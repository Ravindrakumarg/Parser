%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
%}

%option noyywrap

num [0-9]+

%%

{num}	{fprintf(yyout,"%s","num");}
 .	{fprintf(yyout,"%s",yytext);}

%%

int main(int argc, char **argv) {

	char out_file_name[100];
	short len;

	if(argc !=2) {

		printf("<%s> : Missing Arguments!!!",argv[0]);
		exit(EXIT_FAILURE);
	}
	++argv;
	--argc;
	if(argc > 0) {

		yyin = fopen(argv[0],"r");
		if (yyin == NULL) {
			printf("File Opening Error!!!");
			return(EXIT_FAILURE);
		}
	
	}
	strcpy(out_file_name,argv[0]);
	len =strlen(argv[0]);
	out_file_name[len-2]='o';
	out_file_name[len-1]='u';
	out_file_name[len]='t';
	out_file_name[len+1]='\0';
	yyout = fopen(out_file_name,"w");
	yylex();

	return(EXIT_SUCCESS);

}