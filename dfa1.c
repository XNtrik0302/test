#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NUM_STATES 5
#define NUM_SYMBOLS 2

int acceptingState = 3;
char validInputs[NUM_SYMBOLS] = {'0', '1'};
int transitionTable[NUM_STATES][NUM_SYMBOLS] = {
    {1, 2},  // State Q0
    {4, 3},  // State Q1
    {3, 4},  // State Q2
    {1, 2},  // State Q3
    {2, 1}}; // State Q4

bool runDFA(const char *input)
{
    int currentState = 0;

    while (*input != '\0')
    {
        char symbol = *input;
        int symbolIndex = -1;
        for (int j = 0; j < NUM_SYMBOLS; j++)
        {
            if (symbol == validInputs[j])
            {
                symbolIndex = j;
                break;
            }
        }
        if (symbolIndex == -1)
        {
            return false;
        }

        currentState = transitionTable[currentState][symbolIndex];
        input++;
    }

    return currentState == acceptingState;
}

int main()
{
    char input[100];
    do
    {
        printf("Enter a string (0s and 1s): ");
        scanf("%s", input);

        if (runDFA(input))
        {
            printf("Accepted\n");
        }
        else
        {
            printf("Not Accepted\n");
        }
    } while (1);

    return 0;
}