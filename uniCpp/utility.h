double max(double a, double b);
double max(double a, double b, double c);

double mean(double a, double b, double c);
int mean(int a, int b, int c);
bool areEqual(double a, double b);
bool oneNegative(double a, double b, double c);
bool oneZero(double a, double b, double c);
bool allPositive(double a, double b, double c);

/**
 * Returns
 * 0 if all numbers are equal
 * 1 if the numbers are in increasing order
 * 2 if the numbers are in decreasing order
 * 3 if the numbers are in a mixed order
 */
int classify(double a, double b, double c);