#ifndef HOAI_LIB_H
#define HOAI_LIB_H

// Structure to return the fee range
typedef struct {
    int low;
    int max;
} FeeRange;

/**
 * Calculates the lower and upper fee based on anrechenbare Kosten and Honorarzone.
 * Performs linear interpolation if Kosten fall between table brackets.
 *
 * @param anrechenbare_kosten The eligible costs.
 * @param honorarzone The fee zone (1-5).
 * @return FeeRange struct with low and max fee. Returns {-1, -1} on error (e.g., invalid honorarzone or costs out of range).
 */
FeeRange calculate_fee_range_35(int anrechenbare_kosten, int honorarzone);

#endif // HOAI_LIB_H