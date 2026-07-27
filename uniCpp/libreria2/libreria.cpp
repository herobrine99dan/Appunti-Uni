#include "libreria.h"
#include <iostream>

std::string Library::getName()
{
    return name;
}

Item &Library::borrowItem(int id)
{
    // Search item
    int index = -1;

    for (int i = 0; i < items.size(); i++)
    {
        std::cout << "Visualizzo elemento: " << (*items[i]).toString() << std::endl;
        if((*items[i]).getId() == id) {
            index = i;
        }
    }
    if(index == -1) {
        std::cout << "Item not found " << std::endl;
        return *items[0];
    }
    Item& item = (*items[index]);
    // remove item
    items.erase(items.begin() + index);
    return item;
}

void Library::returnItem(Item &item)
{
    items.push_back(&item);
}