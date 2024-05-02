#include <stdio.h>
char str[100];

int isEvenNumberOfZerosAndOnes()
{
    int state = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        char input = str[i];
        switch (state)
        {
        case 0:
            if (input == '0')
                state = 1;
            else if (input == '1')
                state = 2;
            else
                return 0;
            break;
        case 1:
            if (input == '0')
                state = 0;
            else if (input == '1')
                state = 3;
            else
                return 0;
            break;
        case 2:
            if (input == '0')
                state = 3;
            else if (input == '1')
                state = 0;
            else
                return 0;
            break;
        case 3:
            if (input == '0')
                state = 2;
            else if (input == '1')
                state = 1;
            else
                return 0;
            break;
        }
    }

    return (state == 0);
}

int main()
{
    printf("Enter a string of 0s and 1s: ");
    scanf("%s", str);

    if (isEvenNumberOfZerosAndOnes())
    {
        printf("Accepted: The string has an even number of 0s and 1s.\n");
    }
    else
    {
        printf("Rejected: The string does not have an even number of 0s and 1s.\n");
    }

    return 0;
}