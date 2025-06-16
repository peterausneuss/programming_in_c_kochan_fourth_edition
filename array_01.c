#include <stdio.h>
/*
using escape + format specifier to play around with framebuffer and array
Bildschirm löschen: "\033[2J"  
Cursor auf (1,1): "\033[H"  
Cursor auf (Zeile;Spalte): "\033[<Zeile>;<Spalte>H"  
Cursor verstecken: "\033[?25l"  
Cursor anzeigen: "\033[?25h"  
Bildschirm löschen und Cursor auf Anfang: "\033[2J\033[H"  
*/

int main(int argc, char const *argv[])
{
int i,return_value=0;
//char format_String
    printf("\033[2J\033[H");

    for (i = 1; i < 200; i++)
        {
            return_value = printf("\033[0;%iH",i);
            printf("%i",return_value);
            printf("\n");
            printf("\n");
            printf("%i",i);
            if (return_value==8)break;

        }
        
printf("\n");



    return 0;

}

/*





*/