#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("./numeri.txt");
    int n;
    int somma = 0;
    while (fin >> n)
    {
        somma += n;
    }
    cout << "La somma è " << somma << endl;
    fin.close();
}