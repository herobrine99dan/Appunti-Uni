#ifndef ITEM_H
#define ITEM_H

#include <string>
class Item
{
private:
    std::string title;
    int id;
    std::string date;

public:
    Item();
    Item(std::string title, int id, std::string date);
    std::string getTitle();
    int getId();
    std::string getDate();
    virtual std::string toString();
};
#endif