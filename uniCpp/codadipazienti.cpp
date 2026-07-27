#include <iostream>
#include <string>
using namespace std;

class Patient
{
private:
    int id;
    string name;
    string condition;

public:
    Patient(int i, string n, string c)
    {
        this->id = i;
        this->name = n;
        this->condition = c;
    }
    int getId()
    {
        return id;
    }
    string getName()
    {
        return name;
    }
    string getCondition()
    {
        return condition;
    }
    void setId(int i)
    {
        this->id = i;
    }
    void setName(string s)
    {
        this->name = s;
    }
    void setCondition(string c)
    {
        this->condition = c;
    }
    void stampa(ostream &o)
    {
        o << "id: " << id << " name: " << name << " condition: " << condition << endl;
    }
};

template <typename T>
class LinkedNode
{
private:
    T *val;
    LinkedNode *nextNode;

public:
    LinkedNode(T *val, LinkedNode *nextNode)
    {
        this->val = val;
        this->nextNode = nextNode;
    }
    void setNextNode(LinkedNode *node)
    {
        this->nextNode = node;
    }
    T *getValue()
    {
        return val;
    }
    LinkedNode *getNextNode()
    {
        return nextNode;
    }
};

template <typename T>
class Queue
{
private:
    LinkedNode<T> *startNode;
    LinkedNode<T> *endNode;
    void recursivelyDelete(LinkedNode<T> *node)
    {
        if (node == nullptr)
            return;
        recursivelyDelete(node->getNextNode());
        delete node->getValue();
        delete node;
    }

public:
    Queue()
    {
        this->startNode = nullptr;
        this->endNode = nullptr;
    }
    ~Queue()
    {
        recursivelyDelete(startNode);
    }
    void enqueue(T *val)
    {
        LinkedNode<T> *node = new LinkedNode<T>(val, nullptr);
        if (startNode == nullptr)
        {
            this->startNode = node;
            this->endNode = node;
            return;
        }
        /* LinkedNode<T> *iterator = startNode;
        while (iterator->getNextNode() != nullptr)
        {
            iterator = iterator->getNextNode();
        }
                    iterator->setNextNode(node);
*/
        this->endNode->setNextNode(node);
        this->endNode = node;
    }
    T *dequeue()
    {
        if (startNode == nullptr)
        {
            return nullptr;
        }
        if (startNode->getNextNode() == nullptr)
        {
            // Unico nodo
            this->endNode = nullptr;
        }
        T *tempReturn = startNode->getValue();
        LinkedNode<T> *tempNode = startNode;
        this->startNode = tempNode->getNextNode();
        delete tempNode;
        return tempReturn;
    }
    bool isEmpty()
    {
        return startNode == nullptr;
    }
    LinkedNode<T> *getStartNode()
    {
        return startNode;
    }
};

template <typename T>
ostream &operator<<(ostream &s, Queue<T> &q)
{
    LinkedNode<T> *iterator = q.getStartNode();
    while (iterator != nullptr)
    {
        iterator->getValue()->stampa(s);
        iterator = iterator->getNextNode();
    }
    return s;
}

int main()
{
    Queue<Patient> queue;
    queue.enqueue(new Patient(1, "cas", "mb"));
    queue.enqueue(new Patient(2, "ciao", "teas"));
    Patient* a = queue.dequeue();
    Patient* b = queue.dequeue();
    delete a;
    delete b;
    queue.enqueue(new Patient(2, "ciaone", "teasas"));
    cout << queue << endl;
}