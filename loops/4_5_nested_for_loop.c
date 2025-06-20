#include <stdio.h>
// Beispiel für die Eingabe und Schleifen.
// 13.Juni 2025
int main (void){

int i, n, number, quersumme;

for (i=1;i<5;i++)
{
    printf("Input Number: ");
    scanf("%i", &number); //wichtig 
    for (n=1;n<=number;n++)
    quersumme = quersumme+n;
    printf("Die Quersumme von %i ist %i\n", number, quersumme);
    quersumme = 0;
}

return 0;
}