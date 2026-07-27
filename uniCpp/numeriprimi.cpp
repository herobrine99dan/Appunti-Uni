#include <iostream>

bool isPrime(int n)
{
    int divisori = 0;
    for (int i = 2; i < n; i++)
    {
        if (i != n && n % i == 0)
        {
            return false;
        }
    }
    return true;
}

void printAllPrimes(int currentNumber, int howManyComputed, int nLimit)
{
    if(howManyComputed >= nLimit) {
        return;
    }
    if (isPrime(currentNumber))
    {
        std::cout << currentNumber << ",";
        howManyComputed++;
    }
    printAllPrimes(currentNumber + 1, howManyComputed, nLimit);
}

int main()
{
    std::cout << "Quanti numeri primi calcolare? ";
    int n;
    std::cin >> n;
    if (n < 0)
    {
        std::cout << "Scrivere numero positivo" << std::endl;
        exit(1);
    }
    printAllPrimes(2,0, n);
    std::cout << std::endl;
}