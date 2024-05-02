#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_LENGTH 35

FILE *fpin, *fpout;
int line_no = 1, token_no = 0;
char arg[MAX_LENGTH], buffer[MAX_LENGTH];

char keyword[MAX_LENGTH][MAX_LENGTH] = {"auto", "break", "case", "char", "const", "continue", "default",
                                            "do", "double", "else", "enum", "extern", "float", "for", "goto",
                                            "if", "int", "long", "register", "return", "short", "signed",
                                            "sizeof", "static", "struct", "switch", "typedef", "union",
                                            "unsigned", "void", "volatile", "while"};
char separators[] = {';', '{', '}', '(', ')', '?', '@', '!', '%', ',', '&'};
char operators[] = {'+', '-', '*', '/', '='};

int isKeyword(char *identifier)
{
    
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        if (strcmp(identifier, keyword[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isSeparator(char ch)
{
    
    for (int i = 0; i < 11; i++)
    {
        if (ch == separators[i])
        {
            return 1;
        }
    }
    return 0;
}
int isOperator(char ch)
{
    for (int i = 0; i < 5; i++)
    {
        if (ch == operators[i])
        {
            return 1;
        }
    }
    return 0;
}

void printToken(char *token, char *lexeme)
{
    fprintf(fpout, "%-12d%-12d%-24s%s\n", line_no, token_no, token, lexeme);
    token_no++;
}

int main()
{
    char ch;
    fpin = fopen("lexinput.txt", "r");
    fpout = fopen("lexoutput.txt", "w");
    fprintf(fpout, "%-12s%-12s%-24s%s\n", "Line no.", "Token no.", "Token", "Lexeme");
    while ((ch = fgetc(fpin)) != EOF)
    {
        memset(buffer, 0, sizeof(buffer));
        memset(arg, 0, sizeof(arg));
        if (ch == '#')
        {
            fscanf(fpin, "%[^\n]", buffer);
            sprintf(arg, "%c%s", ch, buffer);
            printToken("Preprocessor directive", arg);
        }
        else if (ch == '"')
        {
            fscanf(fpin, "%[^\"]\"", buffer);
            sprintf(arg, "%c%s%c", ch, buffer, ch);
            printToken("Argument", arg);
        }
        else if (isOperator(ch))
        {
            sprintf(arg, "%c", ch);
            printToken("Operator", arg);
        }
        else if (isSeparator(ch))
        {
            sprintf(arg, "%c", ch);
            printToken("Seperator", arg);
        }
        else if (isdigit(ch))
        {
            fscanf(fpin, "%[0-9]", buffer);
            sprintf(arg, "%c%s", ch, buffer);
            printToken("Number", arg);
        }
        else if (isalpha(ch))
        {
            fscanf(fpin, "%[a-zA-Z0-9]", buffer);
            sprintf(arg, "%c%s", ch, buffer);
            if (isKeyword(arg))
            {
                printToken("Keyword", arg);
            }
            else
            {
                printToken("Identifier", arg);
            }
        }
        else if (ch == '\n')
        {
            line_no++;
        }
    }
    fclose(fpin);
    fclose(fpout);
    return 0;
}
