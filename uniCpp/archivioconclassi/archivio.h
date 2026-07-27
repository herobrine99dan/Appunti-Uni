#include "libro.h"
#include <sstream>
#include <fstream>
const int maxBooks = 100;

class Archivio
{

private:
    Libro arr[maxBooks];
    int index = 0;

public:

    bool addBook(Libro& libro);

    void printAllBooks();

    Libro *findBook(std::string title);

    void load(std::string fileName);
    void save(std::string fileName);
};