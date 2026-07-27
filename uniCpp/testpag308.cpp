#include <iostream>

class Test {
int x=5;
public:
Test() {
x=3;
}
int getX() {
return x;
}
};

int main() {
Test();
//std::cout << obj.getX() << std::endl;
}
