#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int credit_num(long cc_num);
bool valid(long cc_num, int len);
string type(long cc_num, int len);

int main(void)
{
    string provider;
    //Get credit card number
    long card_num = get_long("Number: ");
    int len = credit_num(card_num);
    //Number is actually a credit card number
    if (len == 0)
    {
        printf("INVALID\n");
        return 0;
    }
    //Check whether the card is valid
    if (!valid(card_num, len))
    {
        printf("INVALID\n");
        return 0;
    }
    //Check type
    provider = type(card_num, len);
    //print out credit card provider
    printf("%s\n", provider);
}

int credit_num(long cc_num)
{
    //Gets number of digits using log10
    int len = log10(cc_num) + 1;
    //If the number of digits is calid it returns the length else it returns 0
    if (len == 13 || len == 15 || len == 16)
    {
        return len;
    }
    else
    {
        return 0;
    }
}
bool valid(long cc_num, int len)
{
    long divider = pow(10, (len - 1)) + 1e-9;

    int checksum = 0;

    //Calculates checksum
    for (int i = len; i > 0; i--)
    {
        int digit = cc_num / divider;
        if (i % 2 == 0)
        {
            int temp = digit * 2;
            if (temp > 9)
            {
                int tens = temp / 10;
                int ones = temp % 10;
                temp = tens + ones;
            }
            checksum += temp;
            cc_num -= digit * divider;
            divider /= 10;
            continue;
        }
        checksum += digit;
        cc_num -= digit * divider;
        divider /= 10;
    }

    //Checks if checksum is correct
    if (checksum % 10 == 0)
    {
        return true;
    }
    return false;
}
string type(long cc_num, int len)
{

    string type = "INVALID";

    int one_digit = cc_num / (pow(10, (len - 1)) + 1e-9);
    int two_digit = cc_num / (pow(10, (len - 2)) + 1e-9);

    //Checks length then checks starting number
    if (len == 13)
    {
        if (one_digit == 4)
        {
            type = "VISA";
        }
    }
    else if (len == 15)
    {
        if (two_digit == 34 || two_digit == 37)
        {
            type = "AMEX";
        }
    }
    else if (len == 16)
    {
        if (one_digit == 4)
        {
            type = "VISA";
        }
        else if (two_digit == 51 || two_digit == 52 || two_digit == 53 || two_digit == 54 || two_digit == 55)
        {
            type = "MASTERCARD";
        }
    }

    return type;
}