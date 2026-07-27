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

public:
    Studente(int m, string n, string c, float f)
    {
        this->matricola = m;
        this->nome = n;
        this->cognome = c;
        this->media = f;
    }
    virtual ~Studente() {}
    string getNome() { return nome; }
    string getCognome() { return cognome; }
    int getMatricola() { return matricola; }
    float getMedia() { return media; }
    virtual void stampa()
    {
        // matricola: nome cognome- media
        cout << matricola << ":" << " " << getNome() << " " << getCognome() << " - " << media << endl;
    }
};

class BorsaDiStudio
{
private:
    int importo;
    int durata;

public:
    BorsaDiStudio(int i, int d)
    {
        this->importo = i;
        this->durata = d;
    }
    void setImporto(int i)
    {
        this->importo = i;
    }
    void setDurata(int d)
    {
        this->durata = d;
    }
    int getImporto() { return importo; }
    int getDurata() { return durata; }
};

class StudenteBorsista : public Studente
{
private:
    BorsaDiStudio *borsa;

public:
    StudenteBorsista(int m, string n, string c, float f, BorsaDiStudio *borsa) : Studente(m, n, c, f)
    {
        this->borsa = borsa;
    }
    ~StudenteBorsista()
    {
        delete borsa;
    }
    int getImportoBorsa()
    {
        return borsa->getImporto();
    }
    void stampa()
    {
        /*stampa: stampa a video le informazioni dello studente nel formato "matricola: nome cognome
- media [borsa di importo euro]", se è titolare di borsa, altrimenti stampa le informazioni dello
studente senza la borsa.*/
        if (borsa == nullptr)
        {
            Studente stud = *this;
            stud.stampa();
            return;
        }
        cout << getMatricola() << ":" << " " << getNome() << " " << getCognome() << " - " << getMedia() << " [" << "borsa di " << getImportoBorsa() << " euro]" << endl;
    }
};

class LinkedNode
{
private:
    Studente *stud;
    LinkedNode *nextNode;

public:
    LinkedNode(Studente *stud, LinkedNode *nextNode)
    {
        this->stud = stud;
        this->nextNode = nextNode;
    }
    LinkedNode *getNextNode()
    {
        return nextNode;
    }
    void setNextNode(LinkedNode *nextNode)
    {
        this->nextNode = nextNode;
    }
    Studente *getValue()
    {
        return stud;
    }
};

class Stack
{
private:
    LinkedNode *startNode;
    void recursivelyDelete(LinkedNode *node)
    {
        if (node == nullptr)
            return;
        delete node->getValue();
        recursivelyDelete(node->getNextNode());
        delete node;
    }

public:
    Stack()
    {
        startNode = nullptr;
    }
    ~Stack()
    {
        recursivelyDelete(startNode);
    }
    void push(Studente *stud)
    {
        LinkedNode *newNode = new LinkedNode(stud, startNode);
        startNode = newNode;
    }
    Studente *pop()
    {
        if (startNode == nullptr)
            return nullptr;
        LinkedNode *temp = startNode;
        Studente *tempReturn = temp->getValue();
        startNode = temp->getNextNode();
        delete temp->getValue();
        delete temp;
        return tempReturn;
    }
    void filter()
    {
        LinkedNode *previous = nullptr;
        LinkedNode *iterator = getStartNode();
        while (iterator != nullptr)
        {
            Studente *stud = iterator->getValue();
            if (stud->getMedia() < 25)
            {
                cout << "Studente insufficiente rimosso: ";
                stud->stampa();
                if (previous == nullptr)
                { // headnode
                    pop();
                    iterator = getStartNode();
                    previous = nullptr;
                } else { // nothead node
                    previous->setNextNode(iterator->getNextNode());
                    LinkedNode* temp = iterator;
                    iterator = iterator->getNextNode();
                    delete temp->getValue();
                    delete temp;
                }
            }
            else
            {
                previous = iterator;
                iterator = iterator->getNextNode();
            }
        }
    }
    LinkedNode *getStartNode()
    {
        return startNode;
    }
};

int main()
{
    ifstream file("./input2.txt");
    if (!file.good())
    {
        cout << "errore apertura file " << endl;
        return -1;
    }
    Stack stack;
    string tempS;
    while (getline(file, tempS))
    {
        int matricola;
        string nome;
        string cognome;
        float media;
        int borsaImporto;
        int borsaDurata;
        stringstream sStream(tempS);
        sStream >> matricola;
        sStream >> nome;
        sStream >> cognome;
        sStream >> media;
        sStream >> borsaImporto;
        sStream >> borsaDurata;
        Studente *stud;
        if (borsaDurata > 0)
        {
            stud = new StudenteBorsista(matricola, nome, cognome, media, new BorsaDiStudio(borsaImporto, borsaDurata));
        }
        else
        {
            stud = new Studente(matricola, nome, cognome, media);
        }
        stack.push(stud);
        // cout << tempS << endl;
    }
    stack.filter();
    cout << "La pila contiene i seguenti studenti:" << endl;
    LinkedNode *iterator = stack.getStartNode();
    int totImportiBorse = 0;
    while (iterator != nullptr)
    {
        iterator->getValue()->stampa();
        if (StudenteBorsista *d = dynamic_cast<StudenteBorsista *>(iterator->getValue()))
        {
            totImportiBorse += d->getImportoBorsa();
        }
        iterator = iterator->getNextNode();
    }
    cout << "Totale importi borse di studio: " << totImportiBorse << endl;
}