#include <stdio.h>

int recursivePalindromeTest(char string[], int index, int size, int mismatched);

int palindromeTest(char string[], int index);

int main()
{
    char string[] = "otto";
    int size = 5;
    printf("Hai scelto la string: %s\n", string);
    printf("Mismatched: %d\n", palindromeTest(string, size));
}

int palindromeTest(char string[], int size)
{
    return recursivePalindromeTest(string, 0, size, 0);
}

int recursivePalindromeTest(char string[], int index, int size, int mismatched)
{
    if (index >= size - 1)
    {
        return mismatched;
    }
    char reflectedChar = string[size - index - 2];
    printf("Current character: %c, Reflected Char: %c\n", string[index], reflectedChar);
    if (string[index] != reflectedChar)
    {
        mismatched++;
    }
    return recursivePalindromeTest(string, index + 1, size, mismatched);
}