#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main()
{
    cout << "Inserire orario corrente, formato 00:00 24 ore ";
    string str;
    cin >> str;
    stringstream ss(str);
    string temp;
    string ore;
    getline(ss, temp, ':');
    ore = temp;
    getline(ss, temp, ':');

    stringstream ss1(ore);
    int oreI;
    ss1 >> oreI;
    bool PMVar = false;
    if(oreI > 12) {
        PMVar = true;
        oreI-=12;
    }
    cout << "Risultato della conversione: " << oreI << ":" << temp << (PMVar ? " PM" : " AM") << endl;
}