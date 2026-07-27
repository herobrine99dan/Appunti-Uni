#include <iostream>
#include <string>
using namespace std;

template <typename T>
class LinkedNode
{
    // TODO Implement cout stream
private:
    T *value;
    LinkedNode *nextNode;

public:
    LinkedNode(T *value, LinkedNode *nextNode)
    {
        this->value = value;
        this->nextNode = nextNode;
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
    void recursivelyClean(LinkedNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        recursivelyClean(node->getNextNode());
        delete node;
    }

public:
    LinkedList()
    {
        this->startNode = nullptr;
    }
    ~LinkedList()
    {
        recursivelyClean(startNode);
    }
    bool isEmpty()
    {
        return startNode == nullptr;
    }
    T *dequeue()
    {
        LinkedNode<T> *temp = startNode;
        T *returnVal = startNode->getValue();
        startNode = startNode->getNextNode();
        delete temp;
        return returnVal;
    }
    T *pop()
    {
        return dequeue();
    }
    void push(T *value)
    {
        LinkedNode<T> *newNode = new LinkedNode<T>(value, startNode);
        if (startNode == nullptr)
        {
            startNode = newNode;
            return;
        }
        startNode = newNode;
    }
    void enqueue(T *value)
    {
        // TODO Improve caching tail, go from O(n) to O(1)
        LinkedNode<T> *newNode = new LinkedNode<T>(value, nullptr);
        if (startNode == nullptr)
        {
            startNode = newNode;
            return;
        }
        LinkedNode<T> *iterator = startNode;
        while (iterator->getNextNode() != nullptr)
        {
            iterator = iterator->getNextNode();
        }
        iterator->setNextNode(newNode);
    }
    LinkedNode<T> *getStartNode()
    {
        return startNode;
    }
};

template <typename T>
ostream &operator<<(ostream &s, LinkedList<T> &list)
{
    s << "[";
    LinkedNode<T> *iterator = list.getStartNode();
    while (iterator != nullptr)
    {
        s << (*iterator->getValue()) << " ";
        iterator = iterator->getNextNode();
    }
    s << "]";
    return s;
}

class GraphNode
{
private:
    LinkedList<GraphNode> *adjacencyList;
    string name;
    bool visited;

public:
    GraphNode(string val)
    {
        this->adjacencyList = new LinkedList<GraphNode>();
        this->name = val;
    }
    ~GraphNode()
    {
        delete adjacencyList;
    }
    void addAdjancencyGraphNode(GraphNode *node)
    {
        this->adjacencyList->enqueue(node);
    }

    LinkedList<GraphNode> *getAdjancencyList()
    {
        return adjacencyList;
    }
    void setVisited(bool b)
    {
        this->visited = b;
    }
    bool hasBeenVisited()
    {
        return visited;
    }
    string getName()
    {
        return name;
    }
};

ostream &operator<<(ostream &s, GraphNode &g)
{
    s << "nodo-" << g.getName();
    return s;
}

void bfs(GraphNode *startNode)
{
    LinkedList<GraphNode> *queue = new LinkedList<GraphNode>();
    queue->enqueue(startNode);
    startNode->setVisited(true);
    while (!queue->isEmpty())
    {
        GraphNode *node = queue->dequeue();
        cout << *node << "   ";
        LinkedNode<GraphNode> *iterator = node->getAdjancencyList()->getStartNode();
        while (iterator != nullptr)
        {
            if (!iterator->getValue()->hasBeenVisited())
            {
                queue->enqueue(iterator->getValue());
                iterator->getValue()->setVisited(true);
            }
            iterator = iterator->getNextNode();
        }
    }
    cout << endl;
    delete queue;
}

void dfs(GraphNode *startNode)
{
    LinkedList<GraphNode> *queue = new LinkedList<GraphNode>();
    queue->enqueue(startNode);
    startNode->setVisited(true);
    while (!queue->isEmpty())
    {
        GraphNode *node = queue->pop();
        cout << *node << "   ";
        LinkedNode<GraphNode> *iterator = node->getAdjancencyList()->getStartNode();
        while (iterator != nullptr)
        {
            if (!iterator->getValue()->hasBeenVisited())
            {
                queue->push(iterator->getValue());
                iterator->getValue()->setVisited(true);
            }
            iterator = iterator->getNextNode();
        }
    }
    cout << endl;
    delete queue;
}

int main()
{
    GraphNode *nodeOne = new GraphNode("one");
    GraphNode *nodeTwo = new GraphNode("two");
    GraphNode *nodeThree = new GraphNode("three");
    GraphNode *nodeFour = new GraphNode("four");
    GraphNode *nodeFive = new GraphNode("five");
    GraphNode *nodeSix = new GraphNode("six");
    nodeOne->addAdjancencyGraphNode(nodeTwo);
    nodeOne->addAdjancencyGraphNode(nodeFive);

    nodeTwo->addAdjancencyGraphNode(nodeThree);
    nodeTwo->addAdjancencyGraphNode(nodeFive);
    nodeTwo->addAdjancencyGraphNode(nodeOne);

    nodeThree->addAdjancencyGraphNode(nodeTwo);
    nodeThree->addAdjancencyGraphNode(nodeFour);

    nodeFour->addAdjancencyGraphNode(nodeThree);
    nodeFour->addAdjancencyGraphNode(nodeFive);
    nodeFour->addAdjancencyGraphNode(nodeSix);

    nodeFive->addAdjancencyGraphNode(nodeFour);
    nodeFive->addAdjancencyGraphNode(nodeTwo);
    nodeFive->addAdjancencyGraphNode(nodeOne);

    nodeSix->addAdjancencyGraphNode(nodeFour);

    dfs(nodeOne);

    delete nodeOne;
    delete nodeTwo;
    delete nodeThree;
    delete nodeFour;
    delete nodeFive;
    delete nodeSix;
}