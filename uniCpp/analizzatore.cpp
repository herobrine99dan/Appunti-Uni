// Esercitazione C++: “Analizzatore di 3 numeri”
// Scrivi un programma che legge tre valori (come double) e produce un piccolo “report”:
// - massimo e minimo
// - media (double) e media arrotondata (int)
// - classificazione: tutti uguali / crescente / decrescente / misto
// - controlli logici: almeno uno negativo? tutti positivi? almeno uno zero?
// Il tutto usando funzioni, overheading, template, cast e strutture di controllo.

#include <iostream>

using namespace std;

inline double massimo(double a, double b, double c);
//double massimo(double a, double b);

double media(double *valori, int n);
int media(int *valori, int n);

int main() {
    double a,b,c;
    char input_utente;

    do {
        cout << "Inserisci il primo numero: ";
        cin >> a;
        cout << "Inserisci il secondo numero: ";
        cin >> b;
        cout << "Inserisci il terzo numero: ";
        cin >> c;

        cout << "a="<< a<< " b=" << b << " c=" << c << endl;

        cout << "Il massimo dei tre valori è: " << massimo(a,b,c) << endl;



        cout << "Vuoi continuare (s|n): ";
        cin >> input_utente;
    } while(input_utente=='s');

    return 0;
}

double massimo(double a, double b, double c)
{
    return massimo(a,massimo(b,c));
}

double massimo(double a, double b) {
    static int i=0;
    cout << i;
    i++;
    return a > b ? a : b;
}

double media(double *valori, int n)
{
    double somma = 0.0;
    for(int i=0; i<n; i++) {
        somma += *(valori+i);
    }
    return somma / n;
}

int media(int *valori, int n);