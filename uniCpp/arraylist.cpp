#include <iostream>
#include <string>
using namespace std;

template <typename T>
class ArrayList
{
private:
    int currSize;
    int indexLastElem;
    T *array;
    void resize(int newSize)
    {
        T *newArr = new T[newSize];
        for (int i = 0; i < currSize; i++)
        {
            newArr[i] = array[i];
        }
        delete[] array;
        array = newArr;
    }

public:
    ArrayList()
    {
        this->currSize = 64;
        this->indexLastElem = -1;
        this->array = new T[currSize];
    }
    ArrayList(int size)
    {
        this->currSize = size;
        this->indexLastElem = -1;
        this->array = new T[size];
    }
    ~ArrayList()
    {
        delete[] array;
    }
    void add(const T &elem) //TODO Perchè il const mi consente di fare ArrayList.add(5)?
    {
        indexLastElem++;
        if (indexLastElem == currSize)
        {
            resize(currSize + 32);
            currSize += 32;
        }
        this->array[indexLastElem] = elem;
    }

    void clear()
    {
        for (int i = 0; i < indexLastElem; i++)
        {
            // TODO A quanto pare qua il compilatore cerca di convertire 0 in T, nel caso di Integer potrebbe chiamare il costruttore Integer(0)
            array[i] = NULL;
        }
        indexLastElem = -1;
    }

    void remove(int index);

    bool contains(T &elem)
    {
        for (int i = 0; i < indexLastElem + 1; i++)
        {
            if (array[i] == elem)
            {
                return true;
            }
        }
        return false;
    }

    T &get(int index)
    {
        if (index < 0 || index > currSize - 1)
        {
            cout << "ArrayIndexOfOutBounds exception" << endl;
            return array[0];
        }
        return array[index];
    }

    bool isEmpty()
    {
        return indexLastElem == -1;
    }

    int size()
    {
        return indexLastElem + 1;
    }

    void set(T &elem, int index)
    {
        if (index > currSize - 1 || index < 0)
        {
            cout << "Illegal operation" << endl;
            return;
        }
        array[index] = elem;
    }
};

template <typename T>
ostream &operator<<(ostream &s, ArrayList<T> &list)
{
    cout << "[";
    for (int i = 0; i < list.size()-1; i++)
    {
        cout << list.get(i) << ", ";
    }
    cout << list.get(list.size()-1);
    cout << "]";
    return s;
}

int main()
{
    cout << "Test ArrayList" << endl;
    ArrayList<int> list(15);
    cout << "Size is currently: " << list.size() << endl;
    for (int i = 1; i < 5; i++)
    {
        list.add(i);
    }
    cout << "Size is currently: " << list.size() << endl;
    cout << "List Updated: " << list << endl;
    list.clear();
    cout << "Size is currently: " << list.size() << endl;
    for (int i = 1; i < 32; i++)
    {
        list.add(i);
    }
    cout << "List Updated: " << list << endl;
    cout << "Size is currently: " << list.size() << endl;
}