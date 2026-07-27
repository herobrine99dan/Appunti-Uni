#include "book.h"

std::string Book::getAuthor()
{
    return author;
}
std::string Book::toString()
{
    return "Book - " + author + " - " + std::to_string(getId());
}
