%{
    #include <stdio.h>
    int num[2];
    int count=0,sum;
    
%}

%%

[0-9]+ {
    num[count] = atoi(yytext);
    sum += num[count];
    count++;
}
[ \t] ; 
[\n] {
    printf("Sum: %d\n", sum);
    yyterminate();
}

. printf("Unexpected character: %s\n", yytext);

%%

int main() {
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}