#include "item.h"

Item::Item()
{
    this->title = "";
    this->id = -1;
    this->date = "0";
}
Item::Item(std::string title, int id, std::string date)
{
    this->title = title;
    this->id = id;
    this->date = date;
}
std::string Item::getTitle()
{
    return title;
}
int Item::getId()
{
    return id;
}
std::string Item::getDate()
{
    return date;
}
std::string Item::toString()
{
    return "Oggetto: " + title + " data: " + date;
}