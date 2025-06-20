#include <stdio.h>
#include <locale.h>

int main() {
  // Setze das Gebietsschema auf die lokale Einstellung (z.B. Deutsch)
  setlocale(LC_ALL, "");

  double number = 1234567.89;

  // Formatierte Ausgabe mit Tausendertrennzeichen
  printf("Formatierte Zahl: %'.2f\n", number); // das Hochkomma formatiert die Tausender und der (.) die Nachkommastellen

  // Mit einer anderen Gebietsschemaeinstellung (z.B. Englisch)
  setlocale(LC_ALL, "en_US.UTF-8");
  printf("Formatierte Zahl (US): %'.2f\n", number);
  
  return 0;
}
