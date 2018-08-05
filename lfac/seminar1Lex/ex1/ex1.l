%{
#include <stdio.h>
int count;
%}
cifra [0-9]
nr {cifra}+
nrNat \{[1-9]{cifra}\}|\{[1-9]{cifra}{3,}\}|\{cifra\}
secv t(ab)+
%%
\<{nr}\> {fprintf(yyout,"[%s]\n", yytext);}
ab+  {fprintf(yyout,"[%s]\n", yytext);}
info {count++;}
([1-9][0-9]*)?[02468] {fprintf(yyout,"[%s]\n", yytext);}
{nrNat} {fprintf(yyout,"nrNat: [%s]\n", yytext);}
{secv} {fprintf(yyout,"Secv: [%s]\n", yytext);}
.|\n ;  
%%
int main(int argc, char** argv){
FILE *g;
if(argc>0)
 yyin = fopen(argv[1],"r");

if(!(g = fopen("out.txt","w")))
    fprintf(stderr,"eroare creare fisier!");
else
 yyout=g; 

yylex();
fprintf(yyout, "\n%d\n",count);

}



