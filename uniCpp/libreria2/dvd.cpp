#include "dvd.h"

int DVD::getLength()
{
    return length;
}
std::string DVD::toString()
{
    return "DVD - " + std::to_string(length) + " - " + std::to_string(getId());
}