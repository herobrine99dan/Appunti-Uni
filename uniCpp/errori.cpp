// ========================
//  Questo programma contiene un errore di complilazione, uno di linker, uno di traduzione e uno logico.
// ========================
#include <iostream>
#include <cmath>

#define PI 3.14159
#define SQUARE(x) ((x)*(x))

using namespace std;

const double globalFactor = 2.5;
int globalCounter = 0;

double areaCerchio(double r);
void stampaMessaggio();
int somma(int a, int b);
int massimo(int a, int b); 
//void stampaMessaggioFinale();

int main() {
    stampaMessaggio();

    double r = 5.0;
    cout << "Area: " << areaCerchio(r) << endl;

    int totale = somma(3,4);
    cout << "Doppio della somma di 3 e 4: "
         << 2 * totale << endl;

    cout << "Massimo tra 20 e 10: "
         << massimo(20, 10) << endl;

   // stampaMessaggioFinale();

    return 0;
}

double areaCerchio(double r) {
    return PI * SQUARE(r);
}

void stampaMessaggio() {
    cout << "Esempio di struttura di un programma C++" << endl;
    globalCounter++;
}

int somma(int a, int b) {
    return a+b;
}

int massimo(int a, int b) {
    if (a == b)
        return a;  
    else if (a < b)
        return b;   
    else
        return a;   
}
