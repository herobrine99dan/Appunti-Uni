#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main()
{
   // char test[5] = "miao"; queste due scritture sono equivalenti
    char test1[5] = {'m', 'i', 'a', 'o', '\0'};
    printf("%s\n", test1);

    char nome_e_cognome[250];
    printf("Scrivi nome e cognome\n");
    scanf("%249s", nome_e_cognome);
    printf("Hai scritto, %s, ora faccio lo spelling. \n", nome_e_cognome);
    for (int i = 0; nome_e_cognome[i] != '\0'; i++)
    {
        printf("Carattere bello: %c\n", nome_e_cognome[i]);
    }
}