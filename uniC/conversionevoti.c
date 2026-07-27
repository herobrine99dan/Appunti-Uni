#include <stdio.h>

/*
Scrivere un programma che traduca un voto in lettere inserito dall’utente nel
corrispondente voto numerico e lo stampi. I voti in lettere sono 'A', 'B', 'C', 'D' e 'F',
eventualmente seguiti da un segno + o –. I loro valori numerici sono, nell’ordine, 4.0, 3.0, 2.0,
1.0 e 0.0. I voti 'F+' e 'F–' non esistono. Un segno + aumenta il voto numerico di 0.3, mentre
un segno – lo diminuisce della stessa quantità. Il voto 'A+' è comunque uguale a 4.0.
*/

int main()
{
    char votoLettera = 'F';
    char segnoAggiuntivo = 48;
    scanf("%c%c", &votoLettera, &segnoAggiuntivo);
    printf("Lettera %d Segno %d\n", votoLettera, segnoAggiuntivo);
    if (votoLettera < 65 || votoLettera > 71 || votoLettera == 69)
    {
        printf("Scrivi il voto base correttamente, hai scritto %c \n", votoLettera);
        return 0;
    }

    if (segnoAggiuntivo != '+' && segnoAggiuntivo != '-' && segnoAggiuntivo != 10)
    {
        printf("Scrivi il segno correttamente, hai scritto %c \n", segnoAggiuntivo);
        return 0;
    }
    if (votoLettera == 'F' && segnoAggiuntivo != 10)
    {
        printf("Voto non consentito: %c %c\n", votoLettera, segnoAggiuntivo);
        return 0;
    }
    float m = (1 - 2) / (68 - (float)67);
    float q = 1 - m * 68;
    float votoBase = votoLettera == 'F' ? 0 : m * votoLettera + q;
    float addendumSegno = segnoAggiuntivo == '+' ? 0.3f : segnoAggiuntivo == '-' ? -0.3f: 0;
    float votoFinale = votoBase + addendumSegno;
    votoFinale = votoFinale > 4 ? 4 : votoFinale;
    printf("Voto votoBase %f \n", votoFinale);
}
