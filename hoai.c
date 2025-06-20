#include <stdio.h>  // For fprintf, printf (in main)
#include <locale.h> // For setlocale()
#include "hoai_lib.h" // Include our new HOAI library header

// Example main for testing (can be commented out or moved by removing /* and */)

int main() {
    // Set locale for numeric formatting (e.g., thousand separators)
    setlocale(LC_NUMERIC, "");

    // Test cases
    int test_kosten[] = {25000, 299999,10000000, 25000000}; // Added 25000 for boundary, 30M for out-of-range
    int test_zonen[] = {1, 2, 3, 4, 5};

    printf("Anrech. Kosten | HZ | Fee Low    | Fee Max\n");
    // Adjusted separator line to match new column widths (14, 2, 10, 10)
    printf("---------------|----|------------|----------\n");

    for (int i = 0; i < sizeof(test_kosten) / sizeof(test_kosten[0]); ++i) {
        for (int k = 0; k < sizeof(test_zonen) / sizeof(test_zonen[0]); ++k) {
            int kosten = test_kosten[i];
            int zone = test_zonen[k];
            // Call the function from our library
            FeeRange fr = calculate_fee_range(kosten, zone);
            if (fr.low != -1 || fr.max != -1) { // Check if not an error return - use ' for thousand separators
                printf("%'-14d | %-2d | %'-10d | %'-10d\n", kosten, zone, fr.low, fr.max);
            }
        }

        if (i < sizeof(test_kosten) / sizeof(test_kosten[0]) -1) { // Print separator line between cost groups
            printf("---------------|----|------------|----------\n");
        }
    }
    return 0;
}
