#include <iostream>

using namespace std;

int somma(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 2;
    int b = 4;
    int (*puntatoreAFunzione) (int a, int b);
    puntatoreAFunzione = somma;
    int c = puntatoreAFunzione(a, b);
    cout << "Puntatore a funzione " << c << endl;
}