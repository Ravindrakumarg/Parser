#include<stdio.h>
#include<stdlib.h>
#include "header.h"

int process_input_parser_table(struct _start* head,struct _start_follow *head_follow, struct _p_end * head_terminal,  struct _table_head * head_parser_table)
{
	struct _p_end * input_head, *stack_head;	
	struct _p_end * i, *s, *i1, *s1, *node;	

	input_head=NULL;
	stack_head=NULL;	
	
	input_head = make_list_of_input_string(input_head);
	stack_head = make_list_of_stack_string(stack_head,head);
	
	if(input_head->nloc==NULL){
		printf("\nNothing to be enetered by user for parsed\n");
		return(1);
		}	
	while(1){
		i=input_head;
    		s=stack_head;
    		i1=i;
    		s1=s;
		while(i->nloc!=NULL){
			i1=i;
			i=i->nloc;
			}

		while(s->nloc!=NULL){
			s1=s;
        	        s=s->nloc;
			}
		fflush(stdout);
		if(!strcmp("#",s->ch)){
                        printf("\nCode Succesful");
                        break;
                        }

		if(strcmp(i->ch,s->ch)){
			printf("\nUnMatched");
			stack_head = change_stack_symbol(stack_head, input_head, s,i,head_parser_table);
			printf("\n\nList of grammer to be parsed: ");
			display_list(input_head);
			printf("\nstack list after update: ");
			display_list(stack_head);
			}
		else{
			printf("\nMatched");
			i1->nloc=NULL;
			s1->nloc=NULL;
			printf("\ninput list after update: ");
			display_list(input_head);
			printf("\nstack list after update: ");
                        display_list(stack_head);
			}

	}
	printf("\n");
	return(1);
}

struct _p_end * change_stack_symbol(struct _p_end *stack_head, struct _p_end * input_head, struct _p_end * s, struct _p_end * i, struct _table_head * head_parser_table)
{
	struct _p_end * tt,*ploc_tt, * prod, *p_head, *p_head1, *node ;
	struct _table_head  * t_head;
	struct _parser_table *p_table;
	int flag=0;
	
	tt=stack_head;
	t_head=head_parser_table;
	p_head=NULL;	

	ploc_tt=tt;
	while(tt->nloc!=NULL){
		ploc_tt=tt;
		tt=tt->nloc;
		}
	printf("\nprivious:%s, current:%s, input:%s, current:%s",ploc_tt->ch, tt->ch, i->ch, s->ch);
	
	 if("#"==i->ch){
                        printf("\n sonu");
                        node=(struct _p_end *)malloc(sizeof(struct _p_end));
                        node->ch="$";
                        node->nloc=NULL;
                        i->nloc=node;
			i=i->nloc;
                        }
	fflush(stdout);
	printf("\n\n %s",i->ch);
	while(t_head!=NULL){
		flag=strcmp(t_head->ch,i->ch);
		if(flag==0){
			printf("\nTerminal list matched: %s",t_head->ch);
			break;
			}
		t_head=t_head->nloc;
		}

	fflush(stdout);
//	printf("\n1 CONTROL HERE\n");
	
	if(t_head==NULL){
		printf("\nTerminal symbol not found in the list\n");
		exit(1);
		}
	
	p_table=t_head->down;
	
	fflush(stdout);
//	printf("\n2 CONTROL HERE\n");	
	while(p_table!=NULL){
		flag=strcmp(p_table->ch,s->ch);
		if(flag==0){
			printf("\nStarting symbol matched: %s",p_table->ch);
			break;
			}
		p_table=p_table->down;
		}
	if(p_table==NULL){
		printf("\nStarting symbol not found in the list\n");
                exit(1);
		}

	prod=p_table->nloc;
	
	fflush(stdout);
//	printf("\n3 CONTROL HERE\n");	

	if(!strcmp("@",prod->ch)){
		ploc_tt->nloc=NULL;
		}
	else{
		while(prod!=NULL){
			node=(struct _p_end *)malloc(sizeof(struct _p_end));
			node->ch=prod->ch;
			node->nloc=NULL;
	
			fflush(stdout);
//			printf("\n4 CONTROL HERE\n");	

			if(p_head==NULL)
				p_head=node;
			else{
				p_head1=p_head;
				while(p_head1->nloc!=NULL)
					p_head1=p_head1->nloc;

				p_head1->nloc=node;
			}
			prod=prod->nloc;
			
			fflush(stdout);
//			printf("\n5 CONTROL HERE\n");	
		}
		
		fflush(stdout);
//		printf("\n6 CONTROL HERE\n");	

		p_head=reverse_list(p_head);
		ploc_tt->nloc=p_head;
			
		fflush(stdout);
//		printf("\n7 CONTROL HERE\n");	
	}

	fflush(stdout);
//	printf("\n8 CONTROL HERE\n");	

	return(stack_head);
}

struct _p_end * reverse_list( struct _p_end * p_head)
{
	struct _p_end * p1, *p2,  *p3;
	
	fflush(stdout);
//	printf("\n1 IN REVERSE LIST\n");	

	if(p_head != NULL && p_head->nloc!=NULL){
		p1=p_head;
        	p2=p1->nloc;
        	p3=p2->nloc;

        	p1->nloc=NULL;
        	p2->nloc=p1;
	
		fflush(stdout);
//		printf("\n2 IN REVERSE LIST\n");	

        	while(p3!=NULL){
        		p1=p2;
       		        p2=p3;
       		        p3=p3->nloc;
                	p2->nloc=p1;
        	        }
        	p_head=p2;
	}

	return(p_head);
}

struct _p_end * make_list_of_stack_string(struct _p_end * stack_head, struct _start * head)
{
	struct _p_end * node, *t;	

	node=(struct _p_end*)malloc(sizeof(struct _p_end));
        node->ch="#";
        node->nloc=NULL;
	
	stack_head=node;
	
	node=(struct _p_end *)malloc(sizeof(struct _p_end));
	node->ch=head->ch;
	node->nloc=NULL;

	stack_head->nloc=node;
	
	printf("\nList Of Stack symbols: ");
	t=stack_head;
	while(t!=NULL){
		printf("\%s",t->ch);
		t=t->nloc;
		}
	return(stack_head);
}

struct _p_end * make_list_of_input_string(struct _p_end * input_head)
{
	FILE * _fp;
	char ch, temp_ch1[10],* temp_s_ch, *temp_p_ch;
	struct _p_end * node, * t, * tt, *p1, *p2, *p3;
	int i,j;

	input_head=NULL;

	_fp=fopen("input.out","r");
	
	ch=fgetc(_fp);
	while(1){
		if(ch==EOF||ch=='\n'||ch=='#')
			break;
		i=0;

        	while(1){
	       	        if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='$'||ch=='('||ch==')'||ch=='#')
        	        	break;
        	        temp_ch1[i]=ch;
        	        i++;
        	        ch=fgetc(_fp);
        		}

		if(i!=0){
			temp_s_ch=(char *)calloc((i+1),sizeof(char));
                	j=i;
                	i=0;
                	temp_p_ch=temp_s_ch;
	       		while(i<j){
        		        *temp_s_ch=temp_ch1[i];
        		        temp_s_ch++;
        		        i++;
        	        	}
			node=(struct _p_end *)malloc(sizeof(struct _p_end));
                	node->nloc=NULL;
			node->ch=temp_p_ch;
			if(input_head==NULL)
				input_head=node;
			else{
				t=input_head;
				while(t->nloc!=NULL){
					t=t->nloc;
					}
				t->nloc=node;
				}
			}
			
		if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='$'||ch=='('||ch==')'){

			temp_p_ch=(char *)calloc((2),sizeof(char));
			*temp_p_ch=ch;

			node=(struct _p_end *)malloc(sizeof(struct _p_end));
                	node->nloc=NULL;
			node->ch=temp_p_ch;

                        if(input_head==NULL)
                                input_head=node;
                        else{
                                tt=input_head;
                                while(tt->nloc!=NULL){
                            	  	tt=tt->nloc;
					}
                                tt->nloc=node;
                                }
                        ch=fgetc(_fp);
                        }
		}
	
	node=(struct _p_end *)malloc(sizeof(struct _p_end));
        node->nloc=NULL;
	node->ch="#";
	
	tt=input_head;
	if(tt==NULL)
		input_head=node;
	else{
		while(tt->nloc!=NULL)
			tt=tt->nloc;
		tt->nloc=node;
		}
	
	//code for revering the list
	if( input_head->nloc!=NULL ){
                p1=input_head;
                p2=p1->nloc;
                p3=p2->nloc;
		
		p1->nloc=NULL;
		p2->nloc=p1;
		while(p3!=NULL){
			p1=p2;
			p2=p3;
			p3=p3->nloc;
			p2->nloc=p1;
			}
		input_head=p2;
                }
	else{
		//return(input_head);
		}
	
	printf("\nlist is grammer to be parsed: ");
	display_list(input_head);	

	return(input_head);
}

int display_list(struct _p_end * tt)
{
	if(tt==NULL)
		printf("\nList is empty");
        while(tt!=NULL){
                printf("%s",tt->ch);
                tt=tt->nloc;
                }
	return(1);
}
