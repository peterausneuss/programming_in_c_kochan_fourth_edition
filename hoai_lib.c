#include "hoai_lib.h" // For FeeRange and calculate_fee_range declaration
#include <stdio.h>    // For fprintf (used for error messages)
#include <math.h>     // For round()

#define HOAI_COST_BRACKETS 20
#define HOAI_FEE_COLUMNS 7 // 1 (Anrechenbare Kosten) + 1 (HZ I min) + 5 (HZ I-V max)

/*
 * hoai_fee_table
 * Stores the fee schedule based on HOAI §35.
 * Each row represents a cost bracket for "Anrechenbare Kosten".
 * Redundant minimum fees for HZ II-V are eliminated as they equal the max fee of the preceding zone.
 *
 * Columns:
 * [0]: Anrechenbare Kosten (Eligible Costs in Euro)
 * [1]: Honorarzone I - min fee
 * [2]: Honorarzone I - max fee (also serves as Honorarzone II - min fee)
 * [3]: Honorarzone II - max fee (also serves as Honorarzone III - min fee)
 * [4]: Honorarzone III - max fee (also serves as Honorarzone IV - min fee)
 * [5]: Honorarzone IV - max fee (also serves as Honorarzone V - min fee)
 * [6]: Honorarzone V - max fee
 */
static const int hoai_fee_table[HOAI_COST_BRACKETS][HOAI_FEE_COLUMNS] = {
    // Kosten, HZ I min, HZ I max, HZ II max, HZ III max,HZ IV max, HZ V max
    {   25000,     3120,     3657,      4339,      5412,      6094,     6631},
    {   35000,     4217,     4942,      5865,      7315,      8237,     8962},
    {   50000,     5804,     6801,      8071,     10066,     11336,    12333},
    {   75000,     8342,     9776,     11601,     14469,     16293,    17727},
    {  100000,    10790,    12644,     15005,     18713,     21074,    22928},
    {  150000,    15500,    18164,     21555,     26883,     30274,    32938},
    {  200000,    20037,    23480,     27863,     34751,     39134,    42578},
    {  300000,    28750,    33692,     39981,     49864,     56153,    61095},
    {  500000,    45232,    53006,     62900,     78449,     88343,    96118},
    {  750000,    64666,    75781,     89927,    112156,    126301,   137416},
    { 1000000,    83182,    97479,    115675,    144268,    162464,   176761},
    { 1500000,   119307,   139813,    165911,    206923,    233022,   253527},
    { 2000000,   153965,   180428,    214108,    267034,    300714,   327177},
    { 3000000,   220161,   258002,    306162,    381843,    430003,   467843},
    { 5000000,   343879,   402984,    478207,    596416,    671640,   730744},
    { 7500000,   493923,   578816,    686862,    856648,    964694,  1049587},
    {10000000,   638277,   747981,    887604,   1107012,   1246635,  1356339},
    {15000000,   915129,  1072416,   1272601,   1587176,   1787360,  1944648},
    {20000000,  1180414,  1383298,   1641513,   2047281,   2305496,  2508380},
    {25000000,  1436874,  1683837,   1998153,   2492079,   2806395,  3053358}
};

// Example of how to access the data (internal to library):
// int cost_bracket_example = hoai_fee_table[0][0]; // 25000
// int zone1_min_fee_example = hoai_fee_table[0][1]; // 3120

// Helper function for linear interpolation (internal to this library)
static double linear_interpolate_value(double x_target, double x1, double y1, double x2, double y2) {
    if (x1 == x2) {
        // This case implies x_target is at x1 (or x2), so y1 (or y2) is the correct value.
        return y1;
    }
    return y1 + (y2 - y1) * (x_target - x1) / (x2 - x1);
}

FeeRange calculate_fee_range_35(int anrechenbare_kosten, int honorarzone) {
    FeeRange result = {-1, -1}; // Default error return

    // Validate Anrechenbare Kosten: must be within the table's defined range
    if (anrechenbare_kosten < hoai_fee_table[0][0] ||
        anrechenbare_kosten > hoai_fee_table[HOAI_COST_BRACKETS - 1][0]) {
        fprintf(stderr, "Error: Anrechenbare Kosten (%d) must be between %d and %d.\n",
                anrechenbare_kosten, hoai_fee_table[0][0], hoai_fee_table[HOAI_COST_BRACKETS - 1][0]);
        return result;
    }

    // Validate Honorarzone (1-5)
    if (honorarzone < 1 || honorarzone > 5) {
        fprintf(stderr, "Error: Honorarzone must be between 1 and 5. Got: %d\n", honorarzone);
        return result;
    }

    // Array to store the 6 fee components (HZ I min, HZ I max, HZ II max, ..., HZ V max)
    double fee_components[6];

    int lower_bound_row_idx = -1;
    int upper_bound_row_idx = -1;

    // Find the rows bracketing anrechenbare_kosten
    if (anrechenbare_kosten == hoai_fee_table[0][0]) {
        lower_bound_row_idx = 0;
        upper_bound_row_idx = 0; // Indicates direct use of this row's fees
    } else {
        for (int i = 1; i < HOAI_COST_BRACKETS; ++i) {
            if (anrechenbare_kosten <= hoai_fee_table[i][0]) {
                upper_bound_row_idx = i;
                lower_bound_row_idx = i - 1;
                break;
            }
        }
    }

    // Calculate fee components: direct lookup or interpolation
    if (lower_bound_row_idx == upper_bound_row_idx) { // Exact match
        for (int j = 0; j < 6; ++j) {
            fee_components[j] = (double)hoai_fee_table[lower_bound_row_idx][j + 1];
        }
    } else { // Interpolation is needed
            double k_lower = (double)hoai_fee_table[lower_bound_row_idx][0];
            double k_upper = (double)hoai_fee_table[upper_bound_row_idx][0];

            for (int j = 0; j < 6; ++j) {
                double fee_val_lower = (double)hoai_fee_table[lower_bound_row_idx][j + 1];
                double fee_val_upper = (double)hoai_fee_table[upper_bound_row_idx][j + 1];
                fee_components[j] = linear_interpolate_value((double)anrechenbare_kosten, k_lower, fee_val_lower, k_upper, fee_val_upper);
            }
    }

    result.low = (int)round(fee_components[honorarzone - 1]);
    result.max = (int)round(fee_components[honorarzone]);

    return result;
}