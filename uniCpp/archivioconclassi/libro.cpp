#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include "libro.h"

using namespace std;

Libro getBookFromUser()
{
    cin.ignore(1000, '\n');
    cout << "Titolo: ";
    string title;
    getline(cin, title);
    cout << "Autore: ";
    string author;
    getline(cin, author);
    int pubYear;
    while (true)
    {
        cout << "Anno di uscita: ";
        string str;
        getline(cin, str);
        stringstream ss(str);
        ss >> pubYear;
        if (!ss.fail())
        {
            break;
        }
    }

    float price;
    while (true)
    {
        cout << "Prezzo: ";

        string str;
        // cin >> price; If number is not parsable, it crashes
        getline(cin, str);
        stringstream ss(str);
        ss >> price;
        if (!ss.fail())
        {
            break;
        }
    }

    Libro libro;
    cout << "Genere: ";
    cin.getline(libro.type, 20);
    libro.title = title;
    libro.author = author;
    libro.publishYear = pubYear;
    libro.price = price;
    return libro;
}

Libro parseBook(string str)
{
    Libro libro;
    stringstream splittedStream(str);
    string t; // temporary string
    getline(splittedStream, t, ';');
    libro.title = t;
    getline(splittedStream, t, ';');
    libro.author = t;
    // parsing numbers correctly
    int pubYear;
    float price;
    getline(splittedStream, t, ';');
    stringstream ss(t);
    ss >> pubYear;
    libro.publishYear = pubYear;

    getline(splittedStream, t, ';');
    stringstream ss1(t);
    ss1 >> price;
    libro.price = price;

    getline(splittedStream, t, ';');
    if(t.length() < 21) {
        strcpy(libro.type, t.c_str());
    }
    return libro;
}