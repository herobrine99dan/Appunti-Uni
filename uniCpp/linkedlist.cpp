#include <iostream>
using namespace std;
template <typename T>
class LinkedNode
{
private:
    T obj;
    LinkedNode *nextNode;

public:
    LinkedNode(T obj)
    {
        this->obj = obj;
        this->nextNode = NULL;
    }
    T &getValue()
    {
        return obj;
    }
    LinkedNode<T> *getNextNode()
    {
        return nextNode;
    }
    void setNextNode(LinkedNode<T> *node)
    {
        this->nextNode = node;
    }
};

template <typename T>
class LinkedList
{
private:
    LinkedNode<T> *startNode;
    void cleanRecursively(LinkedNode<T> *elem)
    {
        if (elem == NULL)
        {
            return;
        }
        cleanRecursively(elem->getNextNode());
        delete elem;
    }

public:
    LinkedList()
    {
        this->startNode = NULL;
    }
    ~LinkedList()
    {
        clear(); // ATTENZIONE, SE QUESTO METODO VIENE CHIAMATO DUE VOLTE E CAUSA HEAP USE AFTER FREE, VUOL DIRE CHE DA QUALCHE PARTE IL COMPILATORE HA FATTO UNA SHALLOW COPY, OVVERO UN PASSAGGIO PER VALORE CON CONSEGUENTE COPIATURA DI DATI
    }
    void addLast(T elem)
    { // Corresponds to offer for queues
        LinkedNode<T> *newNode = new LinkedNode(elem);
        if (isEmpty())
        { // isEmpty()
            startNode = newNode;
            return;
        }
        LinkedNode<T> *lastElem = startNode;
        while (lastElem->getNextNode() != NULL)
        {
            lastElem = lastElem->getNextNode();
        }
        lastElem->setNextNode(newNode);
    }
    void addAll(LinkedList<T>& list)
    {
        LinkedNode<T> *iterator = list.startNode;
        while (iterator->getNextNode() != NULL)
        {
            addLast(iterator.getValue());
            iterator = iterator->getNextNode();
        }
    }

    void addFirst(T elem)
    { // Corresponds to push for stacks
        LinkedNode<T> *newNode = new LinkedNode(elem);
        newNode->setNextNode(this->startNode);
        this->startNode = newNode;
    }

    T removeFirst()
    { // Corresponds to pop for stacks and queues
        if(isEmpty()) {
            cout << "WARNING: Popping from empty list" << endl;
            return T();
        }
        LinkedNode<T>* temp = startNode;
        startNode = temp->getNextNode();
        T returnVal = temp->getValue();
        delete temp;
        return returnVal;
    }
    void clear()
    {
        cleanRecursively(startNode);
    }
    LinkedNode<T> *getStartNode()
    {
        return startNode;
    }
    bool contains(T elem)
    {
        LinkedNode<T> *iterator = startNode;
        while (iterator->getNextNode() != NULL)
        {
            if (elem == iterator->getValue())
            {
                return true;
            }
            iterator = iterator->getNextNode();
        }
        return false;
    }
    bool isEmpty()
    {
        return size() == 0;
    }

    int size()
    {
        if (startNode == NULL)
        {
            return 0;
        }
        int counter = 0;
        LinkedNode<T> *iterator = startNode;
        while (iterator != NULL)
        {
            iterator = iterator->getNextNode();
            counter++;
        }
        return counter;
    }
};

template <typename T>
ostream &operator<<(ostream &s, LinkedList<T>& list) //PASSARE SEMPRE PER RIFERIMENTO TUTTE LE COSE (QUANDO POSSIBILE)
{
    cout << "[";
    if (!list.isEmpty())
    {
        LinkedNode<T> *iterator = list.getStartNode();
        while (iterator != NULL)
        {
            cout << iterator->getValue() << ", ";
            iterator = iterator->getNextNode();
        }
    }
    cout << "]";
    return s;
}

int main()
{
    cout << "LinkedList test" << endl;
    LinkedList<int> list;
    cout << "Size of list is: " << list.size() << endl;
    list.addFirst(1);
    list.addFirst(2);
    list.addFirst(3);
    list.addFirst(4);
    cout << "Size of list now is: " << list.size() << endl;
    //list->removeFirst();
    cout << (list) << endl;
    //delete list;
}

