%{
#include <stdio.h>
#include <string.h>

char word_buffer[100]; 
int word_count = 0;
%}

%%

[a-zA-Z]+ { 
    if (strcmp(yytext, word_buffer) == 0) {
        word_count++;
    }
}

%%

int main() {
    FILE *file;
    file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }
    printf("Enter the word to search: ");
    scanf("%s", word_buffer);
    yyin = file;
    yylex();
    return 0;
}

int yywrap() {
    printf("Word found %d times.\n", word_count);
    fclose(yyin);
    return 1;
}
