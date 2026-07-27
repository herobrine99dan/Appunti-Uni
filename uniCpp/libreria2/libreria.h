#include <string>
#include <vector>
#include "item.h"
class Library {
    private:
    std::string name;
    std::vector<Item*> items;

    public:
    Library(std::string name) {
        this->name = name;
        this->items = {};
    }
    std::string getName();
    Item& borrowItem(int id);
    void returnItem(Item& item);

};