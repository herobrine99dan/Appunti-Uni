#include <iostream>
using namespace std;
class C {
public:
 int T = 0; // Errore
const int CInt = 25; // Errore
int& Dint = T; // Errore
 };

int main() {
cout << "Miao" << endl;
C obj;
cout << "T: " << obj.T << endl;
cout << "CInt: " << obj.CInt << endl;
cout << "Dint: " << obj.Dint << endl;
}
