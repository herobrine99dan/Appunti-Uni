#include <iostream>
using namespace std;

class TreeNode
{
    int val;
    TreeNode *leftNode;
    TreeNode *rightNode;

public:
    TreeNode(int val)
    {
        this->val = val;
        this->leftNode = nullptr;
        this->rightNode = nullptr;
    }
    int getValue()
    {
        return val;
    }
    TreeNode *getLeftNode()
    {
        return leftNode;
    }
    TreeNode *getRightNode()
    {
        return rightNode;
    }
    void insert(TreeNode *node)
    {
        if (node->getValue() >= this->getValue()) // Go right
        {
            if (this->getRightNode() == nullptr)
            { // Add directly
                rightNode = node;
            }
            else
            {
                this->getRightNode()->insert(node);
            }
        }
        else // Go left
        {
            if (this->getLeftNode() == nullptr)
            { // Add directly
                leftNode = node;
            }
            else
            {
                this->getLeftNode()->insert(node);
            }
        }
    }

    TreeNode *searchNode(int val)
    { // Ricerca binaria
        if (val == getValue())
        {
            return this;
        }
        if (val >= getValue())
        {
            if (this->getRightNode() == nullptr)
            {
                return nullptr; // Nodo assente
            }
            return this->getRightNode()->searchNode(val);
        }
        else
        {
            if (this->getLeftNode() == nullptr)
            {
                return nullptr;
            }
            return this->getLeftNode()->searchNode(val);
        }
    }
    int maxElem()
    {
        TreeNode *currMax = this;
        while (currMax->getRightNode() != nullptr)
        {
            currMax = currMax->getRightNode();
        }
        return currMax->getValue();
    }
    int minElem()
    {
        TreeNode *currMin = this;
        while (currMin->getLeftNode() != nullptr)
        {
            currMin = currMin->getLeftNode();
        }
        return currMin->getValue();
    }
};

class Tree
{
private:
    TreeNode *startNode;
    void recursivelyDelete(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        recursivelyDelete(node->getLeftNode());
        recursivelyDelete(node->getRightNode());
        delete node;
    }

public:
    Tree()
    {
        this->startNode = nullptr;
    }
    ~Tree()
    {
        recursivelyDelete(startNode);
    }
    void insert(int val)
    {
        TreeNode *newNode = new TreeNode(val);
        if (startNode == nullptr)
        {
            startNode = newNode;
            return;
        }
        startNode->insert(newNode);
    }
    void preOrder(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        cout << node->getValue() << " ";
        preOrder(node->getLeftNode());
        preOrder(node->getRightNode());
    }
    void inOrder(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        inOrder(node->getLeftNode());
        cout << node->getValue() << " ";
        inOrder(node->getRightNode());
    }
    void postOrder(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        postOrder(node->getLeftNode());
        postOrder(node->getRightNode());
        cout << node->getValue() << " ";
    }
    int max()
    {
        return getRootNode()->maxElem();
    }
    int min()
    {
        return getRootNode()->minElem();
    }
    TreeNode *findSuccessor(int target)
    {
        TreeNode *successor = nullptr;
        TreeNode *iterator = startNode;
        while (iterator != nullptr)
        {
            if (target >= iterator->getValue())
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
    
    TreeNode *searchNode(int val)
    {
        return getRootNode()->searchNode(val);
    }
    TreeNode *getRootNode()
    {
        return startNode;
    }
};

int main()
{
    Tree tree;
    for (int i = 0; i < 10; i++)
    {
        int rNum = rand() % 100 - 50;
        tree.insert(rNum);
    }
    cout << "preorder: ";
    tree.preOrder(tree.getRootNode());
    cout << endl;
    cout << "inorder: ";
    tree.inOrder(tree.getRootNode());
    cout << endl;
    cout << "postorder: ";
    tree.postOrder(tree.getRootNode());
    cout << endl;
    cout << tree.searchNode(43) << endl;
    cout << "successore: " << tree.findSuccessor(-35)->getValue() << endl;
    cout << "Max: " << tree.max() << endl;
    cout << "Min: " << tree.min() << endl;
}