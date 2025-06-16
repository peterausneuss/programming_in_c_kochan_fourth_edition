#include <stdio.h>

int main()
{
    int array_values[10] = {0,1,4,9,16};
    int i;
    char word[] = "Hallo Welt!";
    char input[] = "X";
// Prompt the user and use a width specifier with scanf to prevent overflow.
// "%99s" tells scanf to read at most 99 characters, leaving room for the null terminator.
// Alternatively, consider using fgets: fgets(input, sizeof(input), stdin);
// (though fgets includes the newline if it fits, which might need to be removed).

    for (i = 5; i < 10; i++)
        {
            array_values[i] = i*i;

        }
    for (i = 0; i < 10; i++)    
        {
            printf("Zähler:%i\tWert:%i\n", i, array_values[i]);

        }
scanf("%1s", input);
printf("\033[2J");
printf("CHAR printing\n");
i = 0;

while (word[i])
    {
        printf("%c", word[i]);
        i++;
    }
scanf("%1s", input); 
return 0;
}

