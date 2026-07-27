#include "book.h"
#include "dvd.h"
#include "libreria.h"
#include <iostream>

void printItem(Item &i)
{
    std::cout << i.toString() << std::endl;
}

int main()
{
    Library library("alessandria");
    Book book("miao", 1, "2024", "gatto");
    DVD dvd("le avventure", 2, "2023", 60);
    library.returnItem(book);
    library.returnItem(dvd);
    printItem(library.borrowItem(0));
    printItem(dvd);
    return 0;
}