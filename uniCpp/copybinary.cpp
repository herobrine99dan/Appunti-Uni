#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string fileName;
    cout << "Scrivere file da ricopiare: ";
    cin >> fileName;
    ifstream input(fileName, ios::in | ios::binary);
    if(!input.good()) {
        cout << "Impossibile leggere il file" << endl;
        exit(1);
    }
    ofstream output("output.bin", ios::out | ios::binary);
    char c;
    while(input.get(c)) {
        output.put(c);
    }
    input.close();
    output.close();
}