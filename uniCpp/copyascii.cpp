#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
int main()
{

    cout << "Scrivere nome file con estensione: ";
    string fileName;
    cin >> fileName;
    string temp;
    ofstream outputStream("output.txt");
    ifstream inputStream(fileName);
    if(!inputStream.good()) {
        cout << "Impossibile leggere lo stream" << endl;
        exit(1);
    }
    while(getline(inputStream,temp)) {
        outputStream << temp << endl;
    }
    inputStream.close();
    outputStream.close();
}