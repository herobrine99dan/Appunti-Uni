#include <iostream>
#include <cstdlib>
using namespace std;

class TreeNode
{
private:
    TreeNode *left;
    TreeNode *right;
    int value;

public:
    TreeNode(int val)
    {
        this->left = nullptr;
        this->right = nullptr;
        this->value = val;
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
        return value;
    }

    void insert(TreeNode *newNode)
    {
        if (newNode->getValue() >= value)
        { // greater or equal goes to the right
            if (this->right != nullptr)
            {
                this->right->insert(newNode);
                return;
            }
            this->right = newNode;
        }
        else
        { // lesser goes to the left
            if (this->left != nullptr)
            {
                this->left->insert(newNode);
                return;
            }
            this->left = newNode;
        }
    }
};

class Tree
{
private:
    TreeNode *startNode;
    void recursivelyClean(TreeNode *currNode)
    {
        if (currNode == nullptr)
        {
            return;
        }
        recursivelyClean(currNode->getLeftNode());
        recursivelyClean(currNode->getRightNode());
        delete currNode; // using postOrder visit
    }

public:
    Tree()
    {
        this->startNode = nullptr;
    }
    ~Tree()
    {
        recursivelyClean(startNode);
    }
    void insert(int val)
    {
        TreeNode *node = new TreeNode(val);
        if (startNode == nullptr)
        {
            startNode = node;
            return;
        }
        startNode->insert(node);
    }
    TreeNode *getRootNode()
    {
        return startNode;
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
}
