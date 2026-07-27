#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

//Not using namespaces
struct Libro
{
    std::string title;
    std::string author;
    int publishYear;
    float price;
    char type[21];

    void printBook()
    {
        std::cout << "Libro con titolo " << "Titolo: " << title << " Autore: " << author << " Anno: " << publishYear << " Prezzo: " << price << " Genere: " << type << std::endl;
    }
};

Libro getBookFromUser();

Libro parseBook(std::string str);