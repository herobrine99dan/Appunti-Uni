#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Studente
{
private:
    int matricola;
    string nome;
    string cognome;
    float media;
    // costruttore di copia
public:
    Studente(int m, string n, string c, float f)
    {
        matricola = m;
        nome = n;
        cognome = c;
        media = f;
    }
    Studente(const Studente &other)
    {
        matricola = other.matricola;
        nome = other.nome;
        cognome = other.cognome;
        media = other.media;
    }
    string getNome()
    {
        return nome;
    }
    int getMatricola()
    {
        return matricola;
    }
    string getCognome()
    {
        return cognome;
    }
    float getMedia()
    {
        return media;
    }
    void stampa()
    {
        cout << "matricola: " << matricola << " nome: " << nome << " cognome:" << cognome << " media: " << media << endl;
    }
};

class TreeNode
{
private:
    Studente *val;
    TreeNode *right;
    TreeNode *left;

public:
    TreeNode(Studente *v)
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
    Studente *getValue()
    {
        return val;
    }
    Studente *min()
    {
        TreeNode *iterator = this;
        while (iterator->getLeftNode() != nullptr)
        {
            iterator = iterator->getLeftNode();
        }
        return iterator->getValue();
    }
    Studente *max()
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
        if (node->getValue()->getMatricola() >= getValue()->getMatricola())
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
    TreeNode *search(int matr)
    {
        // Binary Search
        if (getValue()->getMatricola() == matr)
        {
            return this;
        }
        if (matr >= getValue()->getMatricola())
        {
            if (getRightNode() == nullptr)
            {
                return nullptr;
            }
            TreeNode *founded = getRightNode()->search(matr);

            return founded;
        }
        else
        {
            if (getLeftNode() == nullptr)
            {
                return nullptr;
            }
            TreeNode *founded = getLeftNode()->search(matr);

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
        delete node->getValue();
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
        node->getValue()->stampa();
        inOrder(node->getRightNode());
    }
    void insert(Studente *val)
    {
        TreeNode *node = new TreeNode(val);
        if (startNode == nullptr)
        {
            this->startNode = node;
            return;
        }
        startNode->insert(node);
    }
    Studente *min()
    {
        return startNode->min();
    }
    Studente *max()
    {
        return startNode->max();
    }
    TreeNode *getRootNode()
    {
        return startNode;
    }
    TreeNode *search(int matr)
    {
        return startNode->search(matr);
    }
};

int main()
{
    Tree *tree = new Tree();
    ifstream fss("./input.txt");
    string s;
    while (getline(fss, s))
    { // each line is a student
        stringstream ss(s);
        string s1;
        string nome;
        string cognome;
        int matr;
        float media;
        //cout << "new student" << endl;
        int column = 0;
        while (getline(ss, s1, ','))
        {
            stringstream streamForReading(s1);
            if (column == 0)
            {
                streamForReading >> matr;
            }
            if (column == 1)
            {
                nome = s1;
            }
            if (column == 2)
            {
                cognome = s1;
            }
            if (column == 3)
            {
                streamForReading >> media;
            }
            column++;
            //cout << "Read from file: " << s1 << endl;
        }
        Studente* stud = new Studente(matr, nome, cognome, media);
        tree->insert(stud);
    }
    fss.close();
    TreeNode* founded = tree->search(1004);
    cout << "nodo trovato:" << endl;
    founded->getValue()->stampa();
    cout << "inorder:" << endl;
    tree->inOrder(tree->getRootNode());
    delete tree;
}