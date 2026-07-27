#include <string>
#include "item.h"

class DVD : public Item
{
private:
    int length;

public:
    DVD(std::string title, int id, std::string date, int length) : Item(title, id, date)
    {
        this->length = length;
    }
    int getLength();
    std::string toString() override;
};