#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include "archivio.h"

using namespace std;

int main()
{
    Archivio archive;
    cout << "Programma bello per gestire array di libri." << endl;
    archive.load("./archivio.txt");
    while (true)
    {
        cout << "Cosa vuoi fare? " << endl
             << "1 -> Aggiungere libro" << endl
             << "2 -> Visualizzare i libri" << endl
             << "3 -> Cercare un libro per nome" << endl
             << "4 -> Salvare e uscire" << endl;
        int choice;
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2 && choice != 3 && choice != 4))
        {
            cin.ignore(1000, '\n');
            continue;
        }
        if (choice == 1)
        {
            Libro libro = getBookFromUser();
            if (archive.addBook(libro))
            {
                cout << "È stato aggiunto un ";
                libro.printBook();
            }
            else
            {
                cout << "Limite massimo di libri raggiunto" << endl;
            }
        }
        if (choice == 2)
        {
            archive.printAllBooks();
        }
        if (choice == 3)
        {
            cin.ignore(1000, '\n');
            string title;
            cout << "Titolo libro: ";
            getline(cin, title);
            Libro *book = archive.findBook(title);
            if (book == NULL)
            {
                cout << "Libro non trovato" << endl;
                continue;
            }
            (*book).printBook();
        }
        if (choice == 4)
        {
            archive.save("./archivio.txt");
            exit(0);
        }
    }
}