/*
branch : function with global variables


converting postive Integer to another base 16:hex and 2:bin 
Date: 21. Juni 2025
    using arrays
    input decimal, long int >= 0
    printing
*/
#include <stdio.h>
#include <stdlib.h>
const char baseDigits[16] ={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int convertedNumber_16[64];
int convertedNumber_2[64];
long int numberToConvert, copyNumberToConvert;
int nextDigit, base, index_16, index_2 = 0;

void get_number(void)
{
    // get the number to convert
    printf("Enter a decimal number: ");
    scanf("%ld", &numberToConvert);
    copyNumberToConvert = numberToConvert;
}

void convert_number_16(void)
{
    do
    {

        convertedNumber_16[index_16] = numberToConvert % 16;
        numberToConvert /= 16;
        index_16++;

    } while (numberToConvert != 0);55
}

int main(int argc, char const *argv[])
{


// check if a number is present 
if (argc != 2)
{
get_number();
}
else
{
numberToConvert = atol(argv[1]); //atol konvertiert einen ASCII-String 
//in eine (vorzeichenbehaftete) breite Integerzahl

copyNumberToConvert = numberToConvert;
}

// check NumberToConvert >=0
if (numberToConvert>=0) 
{

// convert number to base 16
convert_number_16();

// convert number to base 2
do{
convertedNumber_2[index_2] = copyNumberToConvert % 2;
copyNumberToConvert /= 2;
index_2++;
} while (copyNumberToConvert != 0);

// print converted number

printf("HEX: ");
for (--index_16; index_16 >= 0; index_16--)
{
    nextDigit = convertedNumber_16[index_16];
    putchar(baseDigits[nextDigit]);
}

printf("\nBIN: ");
for (--index_2; index_2 >= 0; index_2--)
{
    nextDigit = convertedNumber_2[index_2];
    putchar(baseDigits[nextDigit]);
}
printf("\n");
}
else {printf("Converting only postive numbers\n");}


    return 0;
}



