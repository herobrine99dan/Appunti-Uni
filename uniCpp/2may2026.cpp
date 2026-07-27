#include <iostream>
#include <string>
using namespace std;

class Rettangolo
{
private:
    int height;
    int base;
    int area;

public:
    Rettangolo(int h, int b)
    {
        this->height = h;
        this->base = b;
        this->area = h * b;
    }
    Rettangolo()
    {
        this->height = 0;
        this->base = 0;
        this->area = 0 * 0;
    }
    int getArea()
    {
        return area;
    }
    int getBase()
    {
        return base;
    }
    int getHeight()
    {
        return height;
    }
};

template <typename T>
class LinkedNode
{
private:
    T *value;
    LinkedNode *nextNode;

public:
    LinkedNode(T *value, LinkedNode *nextNode)
    {
        this->value = value;
        this->nextNode = nextNode;
    }
    T &getValue()
    {
        return *value;
    }
    LinkedNode *getNextNode()
    {
        return nextNode;
    }
    void setNextNode(LinkedNode *next)
    {
        this->nextNode = next;
    }
};

template <typename T>
class List
{
private:
    LinkedNode<T> *startNode;
    LinkedNode<T> *getTrueStartNode()
    {
        return startNode;
    }

public:
    List(T &dummyNode)
    {
        this->startNode = new LinkedNode<T>(&dummyNode, nullptr);
    }
    ~List()
    {
        clearRecursively(startNode);
    }
    void clearRecursively(LinkedNode<T> *startNode)
    {
        if (startNode == nullptr)
        {
            return;
        }
        clearRecursively(startNode->getNextNode());
        delete startNode;
    }

    void add(T &elem)
    { // Push approach
        LinkedNode<T> *newElem = new LinkedNode<T>(&elem, startNode);
        this->startNode = newElem;
    }

    void remove(LinkedNode<T> *previousElement)
    {
        LinkedNode<T> *currentElem = previousElement->getNextNode();
        previousElement->setNextNode(currentElem->getNextNode());
        delete currentElem;
    }

    void filter(int min, int max)
    {
        LinkedNode<T> *iterator = getStartNode();
        LinkedNode<T> *previous = getTrueStartNode();
        while (iterator != nullptr)
        {
            if (iterator->getValue().getArea() > min && iterator->getValue().getArea() < max)
            {
                iterator = iterator->getNextNode(); // Before removing current element we must go to the next one
                remove(previous);
                continue;
            }
            previous = iterator;
            iterator = iterator->getNextNode();
        }
    }

    LinkedNode<T> *getStartNode()
    {
        return startNode->getNextNode(); // Skipping the dummyNode
    }
};

template <typename T>
ostream &operator<<(ostream &s, List<T> &list)
{
    LinkedNode<T> *iterator = list.getStartNode();
    while (iterator != nullptr)
    {
        s << iterator->getValue() << " ---> ";
        iterator = iterator->getNextNode();
    }
    s << "NULLPTR";
    return s;
}

ostream &operator<<(ostream &s, Rettangolo &rect)
{
    s << "[Height: " << rect.getHeight() << " Base: " << rect.getBase() << " area: " << rect.getArea() << "]";
    return s;
}

int main()
{
    Rettangolo dummyNode(0, 1);
    Rettangolo rect(1, 2);
    Rettangolo rect1(2, 3);
    Rettangolo rect2(3, 4);
    Rettangolo rect3(4, 5);
    Rettangolo rect4(5, 6);
    Rettangolo rect5(6, 7);
    Rettangolo rect6(7, 8);
    List<Rettangolo> *list = new List<Rettangolo>(dummyNode);
    list->add(rect);
    list->add(rect1);
    list->add(rect2);
    list->add(rect3);
    list->add(rect4);
    list->add(rect5);
    list->add(rect6);
    cout << (*list) << endl;
    int min, max;
    cout << "Inserire min: ";
    cin >> min;
    cout << "Inserire max: ";
    cin >> max;
    list->filter(min, max);
    cout << (*list) << endl;
    delete list;
}