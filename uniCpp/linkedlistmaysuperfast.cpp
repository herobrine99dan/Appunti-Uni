#include <iostream>

using namespace std;

template <typename T>
class LinkedNode
{
private:
    LinkedNode *nextNode;
    T *value;

public:
    LinkedNode(T *value, LinkedNode *nextNode)
    {
        this->nextNode = nextNode;
        this->value = value;
    }
    T *getValue()
    {
        return value;
    }
    LinkedNode *getNextNode()
    {
        return nextNode;
    }
    void setNextNode(LinkedNode *nextNode)
    {
        this->nextNode = nextNode;
    }
};

template <typename T>
class LinkedList
{
private:
    LinkedNode<T> *startNode;
    LinkedNode<T> *lastNode;
    void cleanRecursively(LinkedNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        cleanRecursively(node->getNextNode());
        delete node;
    }

public:
    LinkedList()
    {
        this->startNode = nullptr;
        this->lastNode = nullptr;
    }
    ~LinkedList()
    {
        cleanRecursively(startNode);
    }
    LinkedNode<T> *getIterator()
    {
        return startNode;
    }
    void push(T &val)
    {
        LinkedNode<T> *newNode = new LinkedNode(&val, startNode);
        if (startNode == nullptr)
        {
            lastNode = newNode;
        }
        startNode = newNode;
    }
    T *pop()
    {
        if (startNode == nullptr)
        {
            return nullptr;
        }
        if (startNode->getNextNode() == nullptr)
        {
            lastNode = nullptr;
        }
        LinkedNode<T> *temp = startNode;
        startNode = startNode->getNextNode();
        T *returnVal = temp->getValue();
        delete temp;
        return returnVal;
    }
    void enqueu(T &val)
    {
        LinkedNode<T> *newNode = new LinkedNode<T>(&val, nullptr);
        if (startNode == nullptr)
        {
            startNode = newNode;
            lastNode = newNode;
            return;
        }

        /* LinkedNode<T> *lastNode = startNode;
        while (lastNode->getNextNode() != nullptr)
        {
            lastNode = lastNode->getNextNode();
        }*/
        lastNode->setNextNode(newNode); // Caching lastNode for O(1) performance
        lastNode = newNode;
    }
    T *front()
    {
        return startNode;
    }
    T *dequeue()
    {
        return pop();
    }
    void clear()
    {
        cleanRecursively(startNode);
        lastNode = nullptr;
    }
};

template <typename T>
ostream &operator<<(ostream &s, LinkedList<T> &list)
{
    LinkedNode<T> *iterator = list.getIterator();
    while (iterator != nullptr)
    {
        s << (*iterator->getValue()) << ", ";
        iterator = iterator->getNextNode();
    }
    s << "null";
    return s;
}

int main()
{
    LinkedList<int> *list = new LinkedList<int>();
    int a = 5;
    int b = 3;
    int c = 2;
    cout << "TESTING STACK" << endl;
    list->push(a);
    list->push(b);
    list->push(c);
    for (int i = 0; i < 5; i++)
    {
        cout << "list: " << (*list) << endl;
        int *popped = list->pop();
        if (popped == nullptr)
        {
            cout << "Null data, end list" << endl;
            break;
        }
        cout << "popping " << *popped << endl;
    }
    cout << "TESTING QUEUE" << endl;
    list->push(a);
    list->enqueu(b);
    list->enqueu(c);
    for (int i = 0; i < 5; i++)
    {
        cout << "list: " << (*list) << endl;
        int *popped = list->pop();
        if (popped == nullptr)
        {
            cout << "Null data, end list" << endl;
            break;
        }
        cout << "dequeing " << *popped << endl;
    }
    delete list;
}