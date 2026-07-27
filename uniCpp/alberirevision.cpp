#include <iostream>
using namespace std;

template <typename T>
class TreeNode
{
private:
    T value;
    TreeNode *parentNode;
    TreeNode *leftNode;
    TreeNode *rightNode;

public:
    bool dfsVisited = false;
    TreeNode(T value)
    {
        this->value = value;
        parentNode = nullptr;
        leftNode = nullptr;
        rightNode = nullptr;
    }
    T getValue()
    {
        return value;
    }
    TreeNode *getRightNode()
    {
        return rightNode;
    }
    TreeNode *getLeftNode()
    {
        return leftNode;
    }
    TreeNode *getParentNode()
    {
        return parentNode;
    }
    void insert(TreeNode *node)
    {
        if (node->getValue() >= getValue())
        {
            if (getRightNode() == nullptr)
            {
                rightNode = node;
                node->parentNode = this;
                return;
            }
            getRightNode()->insert(node);
        }
        else
        {
            if (getLeftNode() == nullptr)
            {
                leftNode = node;
                node->parentNode = this;
                return;
            }
            getLeftNode()->insert(node);
        }
    }
    TreeNode<T> *min()
    {
        TreeNode *iterator = this;
        while (iterator->getLeftNode() != nullptr)
        {
            iterator = iterator->getLeftNode();
        }
        return iterator;
    }
    TreeNode<T> *max()
    {
        TreeNode *iterator = this;
        while (iterator->getRightNode() != nullptr)
        {
            iterator = iterator->getRightNode();
        }
        return iterator;
    }
    TreeNode *findSuccessor(T val)
    {
        TreeNode *iterator = this;
        TreeNode *successor = nullptr;
        while (iterator != nullptr)
        {
            if (val >= iterator->getValue())
            {
                iterator = iterator->getRightNode();
            }
            else
            {
                successor = iterator;
                iterator = iterator->getLeftNode();
            }
        }
        return successor;
    }
    TreeNode *searchNode(T val)
    {
        if (val == getValue())
        {
            return this;
        }
        if (val >= getValue())
        {
            if (getRightNode() == nullptr)
            {
                return nullptr;
            }
            return getRightNode()->searchNode(val);
        }
        else
        {
            if (getLeftNode() == nullptr)
            {
                return nullptr;
            }
            return getLeftNode()->searchNode(val);
        }
    }
};

template <typename T>
class Tree
{
private:
    TreeNode<T> *rootNode;
    void recursivelyDelete(TreeNode<T> *node)
    {
        if (node == nullptr)
            return;
        // Postorder like deletion
        recursivelyDelete(node->getLeftNode());
        recursivelyDelete(node->getRightNode());
        delete node;
    }

public:
    Tree()
    {
        this->rootNode = nullptr;
    }
    ~Tree()
    {
        recursivelyDelete(rootNode);
    }
    void insert(T val)
    {
        TreeNode<T> *newNode = new TreeNode<T>(val);
        if (rootNode == nullptr)
        {
            rootNode = newNode;
            return;
        }
        rootNode->insert(newNode);
    }
    TreeNode<T> *getRootNode()
    {
        return rootNode;
    }
    void preOrder(TreeNode<T> *node)
    {
        if (node == nullptr)
            return;
        cout << node->getValue() << " ";
        preOrder(node->getLeftNode());
        preOrder(node->getRightNode());
    }
    void inOrder(TreeNode<T> *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->getLeftNode());
        cout << node->getValue() << " ";
        inOrder(node->getRightNode());
    }
    void postOrder(TreeNode<T> *node)
    {
        if (node == nullptr)
            return;
        postOrder(node->getLeftNode());
        postOrder(node->getRightNode());
        cout << node->getValue() << " ";
    }
    TreeNode<T> *findSuccessor(T val)
    {
        return getRootNode()->findSuccessor(val);
    }
    TreeNode<T> *searchNode(T val)
    {
        return getRootNode()->searchNode(val);
    }
    int distanceFromSuccessor(T val)
    {
        TreeNode<T> *nodeFound = searchNode(val);
        if (nodeFound == nullptr)
        {
            cout << "Node not found " << endl;
            return 0;
        }
        TreeNode<T> *successor = findSuccessor(val);
        if (successor == nullptr)
            return 0; // nessun successore
        // Caso 1: il nodo trovato ha una foglia a destra, il successore si trova in basso
        if (nodeFound->getRightNode() != nullptr)
        {
            // scendo al min() del sottoalbero destro, contando gli archi,
            TreeNode<T> *iterator = nodeFound->getRightNode();
            int dist = 1; // perchè vado nel sottoalbero destro
            while (iterator->getLeftNode() != nullptr)
            {
                iterator = iterator->getLeftNode();
                dist++;
            }
            return dist;
        }
        else
        { // Caso 2: il nodo trovato non ha foglia destra, il successore si trova sopra
          // risalgo finché non trovo il successore
            TreeNode<T> *iterator = nodeFound;
            int dist = 0;
            while (iterator != successor)
            {
                iterator = iterator->getParentNode();
                dist++;
            }
            return dist;
        }
    }
};

template <typename T>
ostream &operator<<(ostream &s, TreeNode<T> &node)
{
    s << "TreeNode con valore: " << node.getValue();
    return s;
}

int main()
{
    Tree<int> treeInts;
    treeInts.insert(4);
    treeInts.insert(2);
    treeInts.insert(6);
    treeInts.insert(1);
    treeInts.insert(3);
    treeInts.insert(5);
    treeInts.insert(8);
    treeInts.insert(9);
    treeInts.insert(12);
    treeInts.insert(32);
    treeInts.insert(7);
    Tree<char> treeChars;
    treeChars.insert('a');
    treeChars.insert('b');
    treeChars.insert('c');
    treeChars.insert('d');
    treeChars.insert('e');
    treeChars.insert('k');
    treeChars.insert('f');
    treeChars.insert('g');
    treeChars.insert('h');
    treeChars.insert('i');
    treeChars.insert('j');

    cout << "inorder: ";
    treeInts.inOrder(treeInts.getRootNode());
    cout << endl;
    treeChars.inOrder(treeChars.getRootNode());
    cout << endl;
    cout << "Successore TreeInts di 4: " << *treeInts.findSuccessor(4) << endl;
    cout << "Successore TreeInts di 32: " << treeInts.findSuccessor(32) << endl;
    cout << "Successore TreeChars di e: " << *treeChars.findSuccessor('e') << endl;
    cout << "Successore TreeChars di j: " << treeChars.findSuccessor('j') << endl;
    cout << "Distanza: " << treeInts.distanceFromSuccessor(5) << endl;
}