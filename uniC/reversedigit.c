#include <stdio.h>
#include <math.h>

int countDigits(int n)
{
    int digits = 0;
    while (n > 0)
    {
        digits++;
        n /= 10;
    }
    return digits;
}

int reverseDigit(int n)
{
    int tot = 0;
    int maxDigits = countDigits(n);
    int digits = maxDigits;
    printf("There are %d digits.\n", digits);
    while (digits > 0)
    {
        int lastDigit = n % 10; //get last digit
        n /= 10;
        digits--;
        tot += lastDigit * pow(10, digits);
    }
    return tot;
}

int main()
{
    int number = 0;
    printf("%s","Write your number: ");
    scanf("%d",&number);
    if(number < 0) {
        printf("Il numero deve essere positivo o zero. \n");
        return 0;
    }
    printf("reversed: %d\n", reverseDigit(number));
}
