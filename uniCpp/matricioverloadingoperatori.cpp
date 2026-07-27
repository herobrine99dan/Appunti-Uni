#include <iostream>
using namespace std;

class Matrice
{
private:
    float *arr;
    int rows;
    int columns;

public:
    Matrice(int columns, int rows)
    {
        this->rows = rows;
        this->columns = columns;
        this->arr = new float[rows * columns];
    }
    ~Matrice()
    {
        delete[] arr;
    }
    void acquisisci()
    {
        cin.ignore(1000, '\n');
        float f;
        for (int i = 0; i < rows * columns; i++)
        {
            cin >> f;
            arr[i] = f;
        }
    }
    float getValue(int i)
    {
        return arr[i];
    }
    void setValue(int i, float f)
    {
        arr[i] = f;
    }
    int getRows()
    {
        return rows;
    }

    int getColumns()
    {
        return columns;
    }
    Matrice &operator+(Matrice &mat)
    {
        if (mat.getRows() != getRows() || mat.getColumns() != mat.getColumns())
        {
            cout << "Impossibile fare l'operazione, dimensione matrici diversa" << endl;
        }
        Matrice *newMat = new Matrice(getRows(), getColumns());
        for (int i = 0; i < rows * columns; i++)
        {
            newMat->setValue(i, arr[i] + mat.arr[i]);
        }
        return *newMat;
    }
    Matrice &operator*(Matrice &mat)
    {
        if (mat.getRows() != getRows() || mat.getColumns() != mat.getColumns())
        {
            cout << "Impossibile fare l'operazione, dimensione matrici diversa" << endl;
        }
        for (int i = 0; i < rows * columns; i++)
        {
            arr[i] = arr[i] * mat.arr[i];
        }
        return *this;
    }
    Matrice &operator=(Matrice &mat)
    {
        if (mat.getRows() != getRows() || mat.getColumns() != mat.getColumns())
        {
            cout << "Impossibile fare l'operazione, dimensione matrici diversa" << endl;
        }
        for (int i = 0; i < rows * columns; i++)
        {
            arr[i] = mat.arr[i];
        }
        return *this;
    }
};

ostream &operator<<(ostream &s, Matrice &mat)
{
    for (int i = 0; i < mat.getRows() * mat.getColumns(); i++)
    {
        s << mat.getValue(i) << " ";
        if ((i + 1) % mat.getRows() == 0)
        {
            s << endl;
        }
    }
    return s;
}

int main()
{
    Matrice mat(3, 3);
    Matrice mat1(3, 3);
    mat1.acquisisci();
    Matrice &newMat = mat + mat1;
    cout << mat;
    cout << mat1;
    cout << newMat;
    delete &newMat;
}