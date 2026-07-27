#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    cout << "Frase: ";
    string s;
    getline(cin, s);
    cout<< "s is " << s << endl;
    stringstream ss(s);
    string word;
    int words = 0;
    while(ss >> word) {
        words++;
    }
    cout << "Ci sono " << words << " parole" << endl;
}