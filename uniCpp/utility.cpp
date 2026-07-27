#include "utility.h"
#include <cmath>

double mean(double a, double b, double c)
{
    return (a + b + c) / 3;
}

int mean(int a, int b, int c)
{
    double sum = a + b + c;
    return static_cast<int>(sum / 3 + 0.5);
}

bool areEqual(double a, double b)
{
    return abs(a - b) < 0.001;
}

double max(double a, double b)
{
    return a > b ? a : b;
}

double max(double a, double b, double c)
{
    return max(a, max(b, c));
}

bool oneNegative(double a, double b, double c)
{
    return a < 0 || b < 0 || c < 0;
}

bool oneZero(double a, double b, double c)
{
    return areEqual(a, 0) || areEqual(c, 0) || areEqual(b, 0);
}

bool allPositive(double a, double b, double c)
{
    return a > 0 && b > 0 && c > 0;
}

/**
 * Returns
 * 0 if all numbers are equal
 * 1 if the numbers are in increasing order
 * 2 if the numbers are in decreasing order
 * 3 if the numbers are in a mixed order
 */
int classify(double a, double b, double c)
{
    if (areEqual(a, b) && areEqual(b, c) && areEqual(a, c))
    {
        return 0;
    }
    if (a < b && b < c)
    {
        return 1;
    }
    if (a > b && b > c)
    {
        return 2;
    }
    return 3;
}