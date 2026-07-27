#include <iostream>
using namespace std;
class LinkedNode
{
private:
    int val;
    LinkedNode *nextNode;
    int visitedTimes;

public:
    LinkedNode(int i, LinkedNode *nextNode)
    {
        this->val = i;
        this->nextNode = nextNode;
        this->visitedTimes = 0;
    }
    int getValue() { return val; }
    LinkedNode *getNextNode() { return nextNode; }
    void setNextNode(LinkedNode *nextNode)
    {
        this->nextNode = nextNode;
    }
    int howManyVisits()
    {
        return visitedTimes;
    }
    void setHowManyVisits(int i)
    {
        this->visitedTimes = i;
    }
};
class LinkedList
{
private:
    LinkedNode *startNode;
    void recursivelyDelete(LinkedNode *node)
    {
        if (node == nullptr)
            return;
        recursivelyDelete(node->getNextNode());
        delete node; 
    }

public:
    LinkedList()
    {
        this->startNode = nullptr;
    }
    ~LinkedList()
    {
        recursivelyDelete(startNode);
    }
    LinkedNode *add(int i)
    {
        LinkedNode *newNode = new LinkedNode(i, nullptr);
        if (startNode == nullptr)
        {
            startNode = newNode;
            return newNode;
        }
        LinkedNode *iterator = startNode;
        while (iterator->getNextNode() != nullptr)
        {
            iterator = iterator->getNextNode();
        }
        iterator->setNextNode(newNode);
        return newNode;
    }
    LinkedNode *getStartNode()
    {
        return startNode;
    }
};
ostream &operator<<(ostream &s, LinkedList &l)
{
    LinkedNode *iterator = l.getStartNode();
    while (iterator != nullptr)
    {
        cout << iterator->getValue() << " ";
        iterator = iterator->getNextNode();
    }
    return s;
}

//Returns the node responsible of the loop
LinkedNode* dfs(LinkedNode* parent, LinkedNode *node)
{
    if(node->getNextNode() == nullptr) return nullptr;
    if (node->howManyVisits() > 0)
    {
        cout << "Trying to go in already visited node " << node->getValue() << " from node " << parent->getValue() << endl;
        return parent;
    }
    node->setHowManyVisits(node->howManyVisits() + 1);
    return dfs(node, node->getNextNode());
}

/*returns true if loop has been detected and removed, false otherwise
 */
bool detectAndRemoveLoop(LinkedList &list)
{
    LinkedNode* loopNode = dfs(nullptr, list.getStartNode());
    if(loopNode == nullptr) {return false;}
    loopNode->setNextNode(nullptr);
    return true;
}

int main()
{
    LinkedList list;
    list.add(50);
    list.add(20);
    LinkedNode *startLoopNode = list.add(15);
    list.add(4);
    LinkedNode *endLoopNode = list.add(10);
    endLoopNode->setNextNode(startLoopNode);
    cout << "Lista linkata dopo la rimozione del ciclo " << endl;
    detectAndRemoveLoop(list);
    cout << list << endl;
}