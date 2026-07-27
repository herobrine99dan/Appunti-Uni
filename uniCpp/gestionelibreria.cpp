#include <iostream>
#include <string>
using namespace std;

class Item
{
private:
    string title;
    string author;

public:
    Item(string t, string a)
    {
        title = t;
        author = a;
    }
    Item() {
        title = "null";
        author = "null";
    }
    virtual ~Item() {}
    string getTitle()
    {
        return title;
    }
    string getAuthor()
    {
        return author;
    }
    virtual void stampa() {
        cout << "Not implemented" << endl;
    }
};
class Libro : public Item
{
private:
    int pages;

public:
    Libro(string title, string author, int pages) : Item(title, author)
    {
        this->pages = pages;
    }
    int getPages()
    {
        return pages;
    }
    void stampa()
    {
        cout << "Libro " << getTitle() << " di " << getAuthor() << " con " << pages << " pagine" << endl;
    }
};
class DVD : public Item
{
private:
    float length;

public:
    DVD(string title, string author, int length) : Item(title, author)
    {
        this->length = length;
    }
    int getLength()
    {
        return length;
    }
    void stampa()
    {
        cout << "DVD " << getTitle() << " di " << getAuthor() << " con durata" << length << endl;
    }
};

class Libreria
{
private:
    Item **arr;
    int currSize;
    int index = 0;

public:
    Libreria()
    {
        this->currSize = 10;
        this->arr = new Item*[currSize];
    }
    ~Libreria()
    {
        for(int i = 0; i < index; i++) {
            delete arr[i];
        }
        delete[] arr;
    }
    void resizeArray()
    {
        Item **newArr = new Item*[currSize + currSize / 2];
        for(int i = 0; i < currSize; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        this->arr = newArr;
    }
    void add(Item* item)
    {
        if (index == currSize - 1)
        {
            resizeArray();
        }
        arr[index++] = item;
    }
    void stampa() {
        for(int i = 0; i < index; i++) {
            arr[i]->stampa();
        }
    }
    Item* search(string t) {
        for(int i = 0; i < index; i++) {
            if(arr[i]->getTitle()==t) {
                return arr[i];
            }
        }
        return nullptr;
    }
    void chiediEAggiungi() {
        int n;
        string title;
        string author;
        cout << "Cosa vuoi aggiungere? Libro (1) o DVD (2)?" << endl;
        cin >> n;
        cout << "Titolo: ";
        cin >> title;
        cout << "Autore: ";
        cin >> author;
        if(n == 1) {
            int pages;
            cout << "Numero pagine: ";
            cin >> pages;
            Libro* l = new Libro(title, author, pages);
            add(l);
        }
        if(n == 2) {
            float length;
            cout << "Durata: ";
            cin >> length;
            DVD* d = new DVD(title, author, length);
            add(d);
        }
    }
};

int
main()
{
Libreria l;
Libro* i1 = new Libro("as", "b", 5);
DVD* i2 = new DVD("cq", "gf", 2);
l.add(i1);
l.add(i2);
l.stampa();
}