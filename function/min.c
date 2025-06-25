/*
25. Juni 2025
*/
#include <stdio.h>

// Die Signatur `int values[]` ist flexibler als `int values[10]`
// und macht deutlich, dass die Funktion mit Arrays jeder Größe funktioniert.
int min(int values[], int size) {
    // Annahme: size ist immer größer als 0.
    int min_val = values[0];

    // Die Schleife kann bei 1 beginnen, da das erste Element schon in min_val ist.
    for (int i = 1; i < size; i++) {
        if (values[i] < min_val) {
            min_val = values[i];
        }
    }
    return min_val;
} // Das Semikolon hier ist überflüssig.


int main(void)
{
    // Die Funktionsdeklaration (Prototyp) ist hier nicht nötig,
    // da die Definition der Funktion 'min' bereits vor 'main' steht.

    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int anzahl_elemente = sizeof(values) / sizeof(values[0]);
    printf("Die Anzahl der Elemente im Array ist: %d\n", anzahl_elemente);

    printf("Der kleinste Wert ist: %d\n", min(values, 10));

    printf("Value of [0]: %d\n", values[0]);
    printf("Value of [9]: %d\n", values[9]);
    printf("Value of [10]: %d\n", values[10]);
    printf("Value of [11]: %d\n", values[11]);


    return 0;
}