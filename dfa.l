%{
%}

%s Q1 Q2 Q3 DEAD

%%

<INITIAL>1 BEGIN Q1;
<INITIAL>0 BEGIN Q2;

<INITIAL,Q1,Q2,Q3>[^01\n] BEGIN DEAD;
<INITIAL,Q1,Q3>\n BEGIN INITIAL; {printf("Not Accepted\n"); yyterminate();}

<Q1>1 BEGIN INITIAL;
<Q1>0 BEGIN Q3;

<Q2>1 BEGIN Q3;
<Q2>0 BEGIN INITIAL;
<Q2>\n BEGIN INITIAL; {printf("Accepted\n"); yyterminate();}

<Q3>1 BEGIN Q2;
<Q3>0 BEGIN Q1;

<DEAD>[^\n] BEGIN DEAD; 
<DEAD>\n BEGIN INITIAL; {printf("Invalid\n"); yyterminate();} 

%% 

int main(){ 
	printf("Enter String\n"); 
	yylex(); 
	return 0; 
} 

int yywrap(){
	return 1;
}