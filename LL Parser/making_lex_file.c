#include "header.h"

int make_lex_file(FILE *_fp)
{
	struct _p_end *head1,*node,*temp;	
	FILE *_fp_lex;
	char *chh="%{\n#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n%}\n\n";
	char ch1,*temp_ch,p_ch[10],ch2,*temp_ch1,*ch, *yy;
	int i=0,flag,j=0;
	
	head1=NULL;
	flag=1;

	_fp_lex=fopen("lex_file.l","w");
     	fputs(chh,_fp_lex);
     	fputs("%option noyywrap\n\n",_fp_lex);
	ch1=fgetc(_fp);
		
	while(i<10){
		p_ch[i]='0';
		i++;
	}
	i=0;

	while(1){		
		if(ch1==EOF)
			break;
		fputc(ch1,_fp_lex);
		if(ch1!=' ' && flag==1){
			p_ch[i]=ch1;										         
			i++;
			}
		if(ch1==' ')
			flag=0;
		if(ch1=='\n'){
			flag=1;							
			temp_ch=(char*)calloc(i,sizeof(char));
			j=0;
			temp_ch1=temp_ch;
			while(j<i){
				*temp_ch=p_ch[j];
				temp_ch++;
				j++;
			}	
			//printf("\n%s",temp_ch1);
			i=0;
			
			node=(struct _p_end*)malloc(sizeof(struct _p_end));
			node->ch=temp_ch1;
			node->nloc=NULL;
	
			if(head1==NULL)
				head1=node;
			else
				temp->nloc=node;
			temp=node;		
				
			while(i<10){
				p_ch[i]='0';
				i++;
				}
			i=0;
			}
		ch1=fgetc(_fp);
		}					//end of while(1)
	
	ch="%s";
	yy="yytext";
	fputs("\n%%",_fp_lex);
	temp=head1;	
	fputs("\n", _fp_lex);
	while(temp->nloc!=NULL){
		fprintf(_fp_lex,"\n{%s}\t",temp->ch);
		fprintf(_fp_lex,"{fprintf(yyout,\"%s\",\"%s\");}",ch,temp->ch);
		temp=temp->nloc;
		}
	fprintf(_fp_lex,"\n{%s}\t",temp->ch);
	fprintf(_fp_lex,"{fprintf(yyout,\"%s\",\"%s\");}",ch,temp->ch);
	fprintf(_fp_lex,"\n .\t");
	fprintf(_fp_lex,"{fprintf(yyout,\"%s\",%s);}",ch,yy);
	fputs("\n\n%%",_fp_lex);
	
	fputs("\n\nint main(int argc, char **argv) {\n",_fp_lex);	
	fputs("\n\tchar out_file_name[100];",_fp_lex);
	fputs("\n\tshort len;\n",_fp_lex);
	fputs("\n\tif(argc !=2) {\n",_fp_lex);
	fputs("\n\t\tprintf(\"<%s> : Missing Arguments!!!\",argv[0]);",_fp_lex);
	fputs("\n\t\texit(EXIT_FAILURE);\n\t}",_fp_lex);
	
	fputs("\n\t++argv;",_fp_lex);
	fputs("\n\t--argc;",_fp_lex);
	fputs("\n\tif(argc > 0) {\n",_fp_lex);
	fputs("\n\t\tyyin = fopen(argv[0],\"r\");",_fp_lex);	
	fputs("\n\t\tif (yyin == NULL) {",_fp_lex);	
	fputs("\n\t\t\tprintf(\"File Opening Error!!!\");",_fp_lex);
	fputs("\n\t\t\treturn(EXIT_FAILURE);",_fp_lex);
	fputs("\n\t\t}\n\t\n\t}",_fp_lex);

	fputs("\n\tstrcpy(out_file_name,argv[0]);",_fp_lex);
	fputs("\n\tlen =strlen(argv[0]);",_fp_lex);
	fputs("\n\tout_file_name[len-2]='o';",_fp_lex);
	fputs("\n\tout_file_name[len-1]='u';",_fp_lex);
	fputs("\n\tout_file_name[len]='t';",_fp_lex);
	fputs("\n\tout_file_name[len+1]='\\0';",_fp_lex);
	fputs("\n\tyyout = fopen(out_file_name,\"w\");",_fp_lex);
	fputs("\n\tyylex();\n",_fp_lex);
	
	fputs("\n\treturn(EXIT_SUCCESS);\n\n}",_fp_lex);
	fclose(_fp_lex);
}
