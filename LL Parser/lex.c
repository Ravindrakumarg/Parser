#include "header.h"

struct _p_end *head_terminal=NULL;

struct _p_end * travers()
{
	struct _p_end *temp;
	temp=head_terminal;
	
	fflush(stdout);
	printf("\n\n////////////////////////////////////////////////////////////////////////////");	
	if(temp==NULL)
		printf("\nList Is Empty");
	else{
		printf("\n Here is the list of terminal symbol:\n");
		while(temp->nloc!=NULL){
			printf(" %s",temp->ch);
			temp=temp->nloc;
			}
		printf(" %s",temp->ch);
		}
return(head_terminal);
}

int create_terminal_symbol( struct _start * head , struct _p_end * data)
{
	struct _start *temp;
	struct _p_end *node , *temp1;
	int flag;

	flag=0;
	temp=head;

	while(temp!=NULL){
		flag=strcmp(temp->ch,data->ch);
		if(flag==0)
			break;
		temp=temp->down;
		}

	if(flag!=0){
		node=(struct _p_end*)malloc(sizeof(struct _p_end));
		node->nloc=NULL;
		node->ch=data->ch;

		if(head_terminal==NULL){
			head_terminal=node;
			}
		else{
			temp1=head_terminal;
			flag=0;

			while(temp1->nloc!=NULL){
				flag=strcmp(temp1->ch,data->ch);
				if(flag==0)
					break;
				temp1=temp1->nloc;
				}
			flag=strcmp(temp1->ch,data->ch);
			if(flag!=0){
				temp1=head_terminal;
				while(temp1->nloc!=NULL)
					temp1=temp1->nloc;
					
				temp1->nloc=node;
				}
			}
		}

return(1);
}

int traversal(struct _start * head)
{
	struct _start *temp;
	struct _p_start *temp1;	
	struct _p_end *temp2;
	
	temp=head;
	if(head==NULL)
		printf("\n List Is Empty");
	else{	
		printf("\n////////////////////////////////////////////////////////////////////////////");

		printf("\nGrammer IS:-");
		while(temp->down!=NULL){
			printf("\n%s:",temp->ch);
			temp1=temp->nloc;
			while(temp1->down!=NULL){
				temp2=temp1->nloc;
				while(temp2->nloc!=NULL){
					printf("%s",temp2->ch);
					create_terminal_symbol(head,temp2); 
					temp2=temp2->nloc;	
					}
				printf("%s",temp2->ch);
				create_terminal_symbol(head,temp2);
				printf("|");
				temp1=temp1->down;
				}
				temp2=temp1->nloc;
                                while(temp2->nloc!=NULL){
                                        printf("%s",temp2->ch);
					create_terminal_symbol(head,temp2);
                                        temp2=temp2->nloc;
                                        }
                                printf("%s",temp2->ch);
				create_terminal_symbol(head,temp2);
				printf("|");
				temp=temp->down;
			}
			printf("\n%s:",temp->ch);
                        temp1=temp->nloc;
                        while(temp1->down!=NULL){                               
                               temp2=temp1->nloc;
                               while(temp2->nloc!=NULL){
					printf("%s",temp2->ch);
					create_terminal_symbol(head,temp2);			       	
                                        temp2=temp2->nloc;
                                        }               
			       printf("%s",temp2->ch);
			       create_terminal_symbol(head,temp2);
			       printf("|");
                               temp1=temp1->down;
                               }   
				temp2=temp1->nloc;
                                while(temp2->nloc!=NULL){
                                        printf("%s",temp2->ch);
					create_terminal_symbol(head,temp2);
                                        temp2=temp2->nloc;
                                        }
                                printf("%s",temp2->ch);
				create_terminal_symbol(head,temp2);
				printf("|");

		}//main else
		//printf("\n");
return(1);
}

struct _start * make_link_list ( struct _start * head , char * p_ch , char * temp_p_ch , char chh)
{
	int a; 
	struct _start *temp;
	struct _p_start *node1,*temp1,*node11;
	struct _p_end *node2,*node22,*temp2;

	printf("\n %s %s %c ",p_ch ,temp_p_ch ,chh);

	if(head==NULL)
		printf("\n LIst Is empty");
	else{
		temp=head;
		while(strcmp(p_ch,temp->ch)!=0)
			temp=temp->down;
			
		node2=(struct _p_end*)malloc(sizeof(struct _p_end ));
		node2->nloc=NULL;
		node2->ch=temp_p_ch;

		node1=(struct _p_start*)malloc(sizeof(struct _p_start));
		node1->down=NULL;
		node1->nloc=NULL;	
			
		if(chh!='|'){
			if(temp->nloc==NULL){
				temp->nloc=node1;
				node1->nloc=node2;
				}
			else{
				temp1=temp->nloc;
				while(temp1->down!=NULL)
					temp1=temp1->down;

				if(temp1->nloc==NULL){
					temp1->nloc=node2;
					}
				else{
					temp2=temp1->nloc;
					while(temp2->nloc!=NULL)
						temp2=temp2->nloc;

					temp2->nloc=node2;	
					}
				}
			}//end of main if
		else{
			node11=(struct _p_start*)malloc(sizeof(struct _p_start));
			node11->down=NULL;
			node11->nloc=NULL;

			if(temp->nloc!=NULL){
				temp1=temp->nloc;

				if(temp1->down!=NULL)
					temp1=temp1->down;

				if(temp1->nloc==NULL){
					temp1->nloc=node2;
					temp1->down=node1;
					}
				else{
					temp2=temp1->nloc;
					while(temp2->nloc!=NULL)
						temp2=temp2->nloc;

					temp2->nloc=node2;
					temp1->down=node1;
					}
				}
			else{
				temp->nloc=node1;
				node1->nloc=node2;
				node1->down=node11;
				}
			}					//end of main else
		}						//end of parent else 
return(head);
}

struct _start *linked_list(struct _start * head)
{
	FILE *_fp;
	char ch,temp_ch[SIZE],temp_ch1[SIZE],pch,chh;;
	int i,j,k=0,flag=0;
	char *p_ch,*s_ch,*temp_p_ch,*temp_s_ch, *temp_p1_ch; 
	
	_fp=fopen("lang.txt","r");
	ch=fgetc(_fp);
	ch=fgetc(_fp);
	ch=fgetc(_fp);	
	
	while(1)
	{			
		if(ch==EOF)
			break;

                if(ch=='\n'){
			j=0;
			i=0;
        	        while(i<10){		               
				temp_ch[i]='0';
        	                i++;
                                }
			i=0;
                        ch=fgetc(_fp);

                        if(ch=='%')
      				break;

			do{
                                temp_ch[j]=ch;
                                j++;
                                ch=fgetc(_fp);
                                }while(ch!=':');                                                                                              
                        s_ch=(char *)calloc(j,sizeof(char));
                        i=0;
                        p_ch=s_ch;
			while(i<j){
                                *s_ch=temp_ch[i];
                                s_ch++;
                                i++;
                                }			
			ch=fgetc(_fp);
			k=0;
			}
///////////////////////////////////////////////////////////////////////////////////////////
		pch=ch;
		i=0;
		while(i<10){
			temp_ch1[i]='0';
			i++;
			}
		i=0;

		while(1){
			if(ch==' '||ch=='\n')
				break;

			temp_ch1[i]=ch;
			i++;
			ch=fgetc(_fp);
			}
			
			if(temp_ch1[0]!='|'){
				temp_s_ch=(char *)calloc((i+1),sizeof(char));
                		       j=i;
				i=0;
                		temp_p_ch=temp_s_ch;
		
		                while(i<j){
		                	*temp_s_ch=temp_ch1[i];
		                	temp_s_ch++;
		                	i++;
		                	}
				if(ch != '\n')	
					ch=fgetc(_fp);
				//printf("\n (%s) (%s) (%c)",p_ch,temp_p_ch,ch);
				head=make_link_list( head , p_ch , temp_p_ch , ch);
				}
			else{
				ch=fgetc(_fp);
				}
		}								//end of while(1) loop
		ch=fgetc(_fp);
		fgetc(_fp);
		make_lex_file(_fp);
return(head);	
}

struct _start *start_symbol_list(struct _start *head)
{ 
	FILE *_fp,*temp_fp;
	struct _start *node,*temp;
	char ch,temp_ch[SIZE];
	int i=0,j=0;	
	char *s_ch,*p_ch;	

	_fp=fopen("lang.txt","r");
	if(_fp==NULL)
  		printf("\n File is Empty");
         
        fflush(stdout);
        while(1){
        	ch=fgetc(_fp);
		if(ch==EOF)
			break;
		if(ch=='\n'){	
			j=0;
			i=0;

			while(i<10){
                        	temp_ch[i]='0';
                        	i++;
                        	}
			i=0;
			ch=fgetc(_fp);

			if(ch=='%')
				break;
			do{
 				temp_ch[j]=ch;
		 		j++;
				ch=fgetc(_fp);	
		 		}while(ch!=':');	
			
			s_ch=(char *)calloc(j,sizeof(char));			
			i=0;
			p_ch=s_ch;	
			while(i<j){
				*s_ch=temp_ch[i];
				s_ch++;
				i++;			
				}	
			
			node=(struct _start*)malloc(sizeof(struct _start));
			node->ch=p_ch;
			node->down=NULL;
			node->nloc=NULL;	  

			if(head==NULL)
				head=node;
			else
				temp->down=node;	
			temp=node;			
			}
		}       
return(head); 
}

int display(struct _start *head)
{
	struct _start *temp;
	temp=head;
        fflush(stdout);
	       
	if(head==NULL)
		printf("\nList is Empty");
	else{
		printf("\n Starting Symbol List is:");	
		fputs("\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",log_fp);

		fputs("\nList Of The Non-terminal or Starting Symbols Of The Grammer",log_fp);
		while(temp!=NULL){
			fflush(stdout);
			printf("\n %s :",temp->ch);
			fprintf(log_fp,"\n%s:",temp->ch);
			temp=temp->down;	
			}
	}
return(0);
}

int scan()
{
	FILE *_fp, *_temp_fp;
 	char ch;

	_fp=fopen("lang.txt","r");
	_temp_fp=fopen("temp.txt","w");

	fputs("\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",log_fp);
	fputs("\nHere is th original grammer as written in the file by the user:\n",log_fp);
	if(_fp==NULL)
		printf("\n File Does not Exist");
	else{
 		while(1)
                {	
		ch=fgetc(_fp);
 		if(ch==EOF)
 			break;
		fprintf(log_fp,"%c ",ch);
 		switch(ch){
			case ' ': break;
			case '\t':break;
			default:  fputc(ch,_temp_fp); 				
				  printf("%c",ch);	
			}
	        }
	    }						
	return(1);
}					   
