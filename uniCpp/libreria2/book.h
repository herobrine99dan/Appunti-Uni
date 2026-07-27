#include <string>
#include "item.h"

class Book : public Item
{
private:
    std::string author;

public:
    Book(std::string title, int id, std::string date, std::string author) : Item(title, id, date) {
        this->author = author;
    }
    std::string getAuthor();
    std::string toString() override;
};