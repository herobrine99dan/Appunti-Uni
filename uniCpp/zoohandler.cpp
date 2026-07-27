

#include <iostream>
#include <string>
using namespace std;

class Animal
{
private:
    string name;
    int age;

public:
    Animal(string name, int age)
    {
        this->name = name;
        this->age = age;
    }
    virtual void playSound()
    {
        cout << "Not implemented" << endl;
    }
    string getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }
    void printInfo()
    {
        cout << "Nome: " << name << " età: " << age << endl;
    }
    virtual ~Animal()
    {
    }
};

class Dog : public Animal
{
public:
    Dog(string name, int age) : Animal(name, age)
    {
    }
    virtual void playSound()
    {
        cout << "Bau!" << endl;
    }
    virtual ~Dog()
    {
    }
};

class Cat : public Animal
{
public:
    Cat(string name, int age) : Animal(name, age)
    {
    }
    virtual void playSound()
    {
        cout << "Miao!" << endl;
    }
    virtual ~Cat()
    {
    }
};

int main()
{
    Animal **animals = new Animal *[4];
    animals[0] = new Dog("Puppy", 5);
    animals[1] = new Dog("Billy", 7);
    animals[2] = new Cat("Miagolante", 3);
    animals[3] = new Cat("Birba", 9);
    for (int i = 0; i < 4; i++)
    {
        Animal *obj = animals[i];
        obj->printInfo();
        obj->playSound();
    }
    // Cleaning phase
    for (int i = 0; i < 4; i++)
    {
        delete animals[i];
    }
    delete[] animals;
}