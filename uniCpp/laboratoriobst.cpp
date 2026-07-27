#include <iostream>
#include <cstdlib>
using namespace std;

class TreeNode
{
private:
    int val;
    TreeNode *right;
    TreeNode *left;

public:
    TreeNode(int v)
    {
        this->val = v;
        this->right = nullptr;
        this->left = nullptr;
    }
    TreeNode *getLeftNode()
    {
        return left;
    }

    TreeNode *getRightNode()
    {
        return right;
    }
    int getValue()
    {
        return val;
    }
    int min()
    {
        TreeNode *iterator = this;
        while (iterator->getLeftNode() != nullptr)
        {
            iterator = iterator->getLeftNode();
        }
        return iterator->getValue();
    }
    int max()
    {
        TreeNode *iterator = this;
        while (iterator->getRightNode() != nullptr)
        {
            iterator = iterator->getRightNode();
        }
        return iterator->getValue();
    }

    void insert(TreeNode *node)
    {
        if (node->getValue() >= getValue())
        {
            if (getRightNode() == nullptr)
            {
                this->right = node;
                return;
            }
            getRightNode()->insert(node);
        }
        else
        {
            if (getLeftNode() == nullptr)
            {
                this->left = node;
                return;
            }
            getLeftNode()->insert(node);
        }
    }

    TreeNode *search(int v)
    {
        // Binary Search
        if (getValue() == v)
        {
            return this;
        }
        if (v >= getValue())
        {
            if (getRightNode() == nullptr)
            {
                return nullptr;
            }
            TreeNode *founded = getRightNode()->search(v);

            return founded;
        }
        else
        {
            if (getLeftNode() == nullptr)
            {
                return nullptr;
            }
            TreeNode *founded = getLeftNode()->search(v);

            return founded;
        }
    }
};

class Tree
{
private:
    TreeNode *startNode;
    void recursivelyDelete(TreeNode *node)
    {
        if (node == nullptr)
            return; // PostOrder-like visit
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
    void inOrder(TreeNode *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->getLeftNode());
        cout << node->getValue() << " ";
        inOrder(node->getRightNode());
    }
    void insert(int val)
    {
        TreeNode *node = new TreeNode(val);
        if (startNode == nullptr)
        {
            this->startNode = node;
            return;
        }
        startNode->insert(node);
    }
    int min()
    {
        return startNode->min();
    }
    int max()
    {
        return startNode->max();
    }
    TreeNode *getRootNode()
    {
        return startNode;
    }
    TreeNode *search(int v)
    {
        return startNode->search(v);
    }
    TreeNode* successore(int v) {
        TreeNode* iterator = startNode;
        TreeNode* successor = nullptr;
        while(iterator != nullptr) {
            if(v >= iterator->getValue()) {
                iterator = iterator->getRightNode();
            } else {
                successor = iterator;
                iterator = iterator->getLeftNode();
            }
        }
        return successor;
    }
};

ostream &operator<<(ostream &s, TreeNode &t)
{
    cout << "TreeNode val: " << t.getValue();
    return s;
}

int main()
{
    Tree *tree = new Tree();
    for (int i = 0; i < 20; i++)
    {
        tree->insert(rand() % 30 + 1);
    }
    cout << "inorder visit: ";
    tree->inOrder(tree->getRootNode());
    cout << endl;
    cout << "min: " << tree->min() << endl;
    cout << "max: " << tree->max() << endl;
    TreeNode *node = tree->successore(5);
    if (node == nullptr)
    {
        cout << "Successore non trovato" << endl;
    }
    else
    {
        cout << "Successore trovato: " << *node << endl;
    }
    delete tree;
}

/* int main()
{
    Tree *tree = new Tree();
    int n;
    while(n != -1) {
        cout << "Inserire numero ";
        cin >> n;
        if(n!=-1) {
            tree->insert(n);
        }
    }
    cout << "inorder visit: ";
    tree->inOrder(tree->getRootNode());
    cout << endl;
    cout << "min: " << tree->min() << endl;
    cout << "max: " << tree->max() << endl;
    cout << "Inserire numero da cercare: ";
    cin >> n;
    TreeNode* node = tree->search(n);
    if(node == nullptr) {
        cout << "Nodo non trovato" << endl;
    } else {
        cout << "Nodo trovato: " << *node << endl;
    }
    delete tree;
} */