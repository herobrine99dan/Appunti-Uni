#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;
const int maxBooks = 100;
struct Libro
{
    string title;
    string author;
    int publishYear;
    float price;
    char type[21];

    void printBook(int i)
    {
        cout << "Libro numero " << i << " Titolo: " << title << " Autore: " << author << " Anno: " << publishYear << " Prezzo: " << price << " Genere: " << type << endl;
    }
};

struct Tuple
{
    Libro *libro;
    int index;
};

void addBook(Libro arr[], int index)
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

    // cin.ignore(1000, '\n');
    Libro libro;
    cout << "Genere: ";
    cin.getline(libro.type, 20);
    libro.title = title;
    libro.author = author;
    libro.publishYear = pubYear;
    libro.price = price;
    arr[index] = libro;
    cout << "È stato aggiunto un ";
    libro.printBook(index + 1);
}

void printAllBooks(Libro libreria[], int size)
{
    for (int i = 0; i < size; i++)
    {
        libreria[i].printBook(i + 1);
    }
}

Tuple findBook(Libro arr[], int size, string title)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].title.find(title) != string::npos)
        {
            return {&arr[i], i + 1};
        }
    }
    return {{}, -1};
}

void save(Libro arr[], int size)
{
    ofstream outFile("./archivio.txt", ios::out);
    if (outFile.fail())
    {
        cout << "Errori in apertura per scrivere" << endl;
        return;
    }
    for (int i = 0; i < size; i++)
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
    strcpy(libro.type, t.c_str());
    return libro;
}

int load(Libro arr[])
{
    ifstream inFile("./archivio.txt");
    if (inFile.fail())
    {
        cout << "Errori in apertura" << endl;
        return;
    }
    int index = 0;
    string str;
    while (getline(inFile, str))
    {
        cout << "parsing " << str << endl;
        arr[index] = parseBook(str);
        index++;
    }
    inFile.close();
    return index;
}

int main()
{
    Libro libreria[maxBooks];
    int index = 0;
    cout << "Programma bello per gestire array di libri." << endl;
    index = load(libreria);
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
            if (index + 1 == maxBooks)
            {
                cout << "Limite massimo di libri raggiunto" << endl;
                break;
            }
            addBook(libreria, index);
            index++;
        }
        if (choice == 2)
        {
            printAllBooks(libreria, index);
        }
        if (choice == 3)
        {
            cin.ignore(1000, '\n');
            string title;
            cout << "Titolo libro: ";
            getline(cin, title);
            Tuple tuple = findBook(libreria, index, title);
            if (tuple.libro == NULL)
            {
                cout << "Libro non trovato" << endl;
                continue;
            }
            (*(tuple.libro)).printBook(tuple.index);
        }
        if (choice == 4)
        {
            save(libreria, index);
            exit(0);
        }
    }
}