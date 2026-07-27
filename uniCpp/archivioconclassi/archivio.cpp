#include <sstream>
#include <fstream>
#include "archivio.h"

//here we can use namespace
using namespace std;

void Archivio::load(string fileName)
{
    ifstream inFile(fileName);
    if (inFile.fail())
    {
        cout << "Errore in apertura" << endl;
        return;
    }
    string str;
    while (getline(inFile, str))
    {
        // cout << "parsing " << str << endl;
        arr[index] = parseBook(str);
        index++;
        if(index == maxBooks) {
            cout << "Limite massimo di libri raggiunto " << endl;
            break;
        }
    }
    inFile.close();
}
void Archivio::save(string fileName)
{
    ofstream outFile(fileName, ios::out);
    if (outFile.fail())
    {
        cout << "Errori in apertura per scrivere" << endl;
        return;
    }
    for (int i = 0; i < index; i++)
    {
        Libro l = arr[i];
        outFile << l.title << ";" << l.author << ";" << l.publishYear << ";" << l.price << ";" << l.type << endl;
    }
    if (outFile.fail())
    {
        cout << "Errori in scrittura" << endl;
        return;
    }
    outFile.close();
}

Libro *Archivio::findBook(string title)
{
    for (int i = 0; i < index; i++)
    {
        if (arr[i].title.find(title) != string::npos)
        {
            return &arr[i];
        }
    }
    return NULL;
}

bool Archivio::addBook(Libro& libro) //Uso una reference, risparmio memoria e velocizzo il programma
{
    if (index >= maxBooks)
    {
        return false;
    }
    arr[index++] = libro;
    return true;
}

void Archivio::printAllBooks()
{
    for (int i = 0; i < index; i++)
    {
        arr[i].printBook();
    }
}