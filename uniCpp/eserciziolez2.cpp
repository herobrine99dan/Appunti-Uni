// Esercitazione C++: “Analizzatore di 3 numeri”
// Scrivi un programma che legge tre valori (come double) e produce un piccolo “report”:
// - massimo e minimo
// - media (double) e media arrotondata
// - classificazione: tutti uguali / crescente / decrescente / misto
// - controlli logici: almeno uno negativo? tutti positivi? almeno uno zero?
// Il tutto usando funzioni, overheading, template, cast e strutture di controllo.

#include <iostream>
#include <cmath>
#include "utility.h"

using namespace std;

template <typename T>
T minValue(T a, T b) {
    return a < b ? a : b;
}

template <typename T>
T minValue(T a, T b, T c) {
    return min(a,min(b, c));
}

string classifierToString(int pam)
{
    if (pam == 0)
    {
        return "tutti uguali";
    }
    if (pam == 1)
    {
        return "ordine crescente";
    }
    if (pam == 2)
    {
        return "ordine decrescentes";
    }
    return "misto";
}

string boolToString(bool a)
{
    return a ? "Si" : "No";
}

int main()
{
    double a, b, c;
    cout << "Ciao, scrivi il primo numero" << endl;
    cin >> a;
    cout << "Ciao, scrivi il secondo numero" << endl;
    cin >> b;
    cout << "Ciao, scrivi il terzo numero" << endl;
    cin >> c;
    cout << "I tre numeri sono " << a << " " << b << " " << c << endl;
    cout << "Il minimo è " << minValue(a, b, c) << " il massimo è " << max(a, b, c) << endl;
    cout << "Media normale: " << mean(a, b, c) << " e arrotondata " << mean(static_cast<int>(a), static_cast<int>(b), static_cast<int>(c)) << endl;
    bool oneNeg = oneNegative(a, b, c);
    bool aZero = oneZero(a, b, c);
    bool allPos = allPositive(a, b, c);
    cout << "Esiste almeno uno negativo? " << boolToString(oneNeg) << endl;
    cout << "Esiste almeno uno zero? " << boolToString(aZero) << endl;
    cout << "Sono tutti positivi? " << boolToString(allPos) << endl;
    cout << "Classificazione: " << classifierToString(classify(a, b, c)) << endl;
}