#include <stdio.h>

int main(int argc, char const *argv[])
{
int t_int, input_int= 0;
float t_float = 0.0;
printf("Integer eingeben :");
scanf("%i", &input_int);


printf("\ni\t-.2f\t\t.2f\t\t-i\t\td\n");
for (int i = input_int; i <= 10; i++)
{
    t_int = i*1000;
    t_float = i*2.33333333333333333333;
    printf("%i\t%-.2f\t\t%.2f\t\t%-i\t\t%d\n", i, t_float, t_float, t_int, t_int);

}
    



    return 0;
}

// this prrog test some format strings and features