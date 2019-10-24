#include<stdio.h>
#include<stdlib.h>
#include "header.h"

struct _table_head * create_parser_table( struct _start * head, struct _start_follow * head_follow , struct _p_end * head_terminal)
{
	struct _table_head * head_parser_table;
	struct _table_head * node, * head_parser_table1;
	struct _p_end * temp22;
	struct _start * temp;
	
	traversal(head);
	travers();
	travers1(head_terminal);
	first_follow_display(head_follow);
	
	head_parser_table=NULL;
	temp22=head_terminal;
	temp=head;
	
	fflush(stdout);
	if(temp22!=NULL){
		while( temp22 !=NULL ){
			node=(struct _table_head *)malloc(sizeof(struct _table_head ));
			node->down=NULL;
			node->nloc=NULL;
			node->ch=temp22->ch;
			
			if(head_parser_table==NULL){
				head_parser_table=node;
				head_parser_table1=head_parser_table;
				}
			else{
				head_parser_table1->nloc=node;
				head_parser_table1=node;
				}

			temp22=temp22->nloc;
			}
		}
	head_parser_table1->ch="$";
	//display_table(head_parser_table);

	while(temp!=NULL){
		head_parser_table = finding_first_list(head, temp, head_follow,  head_parser_table);
		temp=temp->down;
		}

	display_table(head_parser_table);

printf("\n");		
return(head_parser_table);
}

struct _table_head * finding_first_list( struct _start *  head, struct _start * temp, struct _start_follow * head_follow, struct _table_head * head_parser_table )
{
	struct _p_start * temp1;
	struct _p_end * temp2;	

	temp1=temp->nloc;
	printf("\n%s:",temp->ch);

	while(temp1!=NULL){
		temp2=temp1->nloc;
		printf("	[%s]",temp2->ch);
		head_parser_table = calculate_first_list(head, temp ,temp2, head_follow, head_parser_table);
		temp1=temp1->down;
		}

return(head_parser_table);
}

struct _table_head * calculate_first_list(struct _start * head, struct _start *temp, struct _p_end * temp2, struct _start_follow * head_follow, struct _table_head * head_parser_table )
{
	struct _start * head1, *head2;
	struct _p_end * temp21, *first_list, *node;	
	struct _start_follow * head_follow1;
	int flag;

	head1=head;
	temp21=temp2;
	flag=0;
	first_list=NULL;
	head_follow1=head_follow;

	while(head1!=NULL){
		flag=strcmp(head1->ch, temp21->ch);
		if(flag==0)
			break;
		head1=head1->down;
		}
	if(flag!=0){
		node=(struct _p_end*)malloc(sizeof(struct _p_end));
		node->ch=temp21->ch;
		node->nloc=NULL;
		first_list=node;
		printf("%s",first_list->ch);
		head_parser_table=add_entry_to_table( head,temp, temp2, first_list, head_parser_table, head_follow);		
		}
	else{
		while( strcmp(head_follow1->ch,temp2->ch))
			head_follow1=head_follow1->down;
		
		first_list=head_follow1->ploc;
		node=first_list;
		while(node!=NULL){
			printf("%s",node->ch);
			node=node->nloc;
			}
		head_parser_table=add_entry_to_table( head, temp, temp2, first_list, head_parser_table, head_follow);
	}

return( head_parser_table );
}

struct _table_head * add_entry_to_table( struct _start *head, struct _start *temp, struct _p_end * temp2, struct _p_end * first_list, struct _table_head * head_parser_table, struct _start_follow *head_follow)
{
	struct _p_end * first_list1, *data, *follow_list, *node1, *follow_list1;
	struct _table_head * head_p;
	struct _parser_table * node, *loop_count;	
	struct _start_follow * start_f;	
	struct _start  * head1, *head2; 
	int flag=0, flag1=0;

	first_list1=first_list;
	head_p=head_parser_table;

	data=(struct _p_end *)malloc(sizeof(struct _p_end));
	data->ch="@";
	data->nloc=NULL;

        while(first_list1!=NULL){
		flag1 = strcmp("@",first_list1->ch);
		if(flag1==0)
			break;
	
		first_list1=first_list1->nloc;
		}
	printf(" %d	",flag1);
	if(flag1==0){
		head2=head;
		printf("	%s",temp->ch);
		
		start_f=head_follow;
		
		while(strcmp(start_f->ch,temp->ch))
			start_f=start_f->down;
		
		printf("	%s",start_f->ch);
		follow_list=start_f->nloc;
		
		follow_list1=follow_list;
		
		while(follow_list1!=NULL){
			printf("	%s",follow_list1->ch);
			flag=strcmp("$",follow_list1->ch);
			if(flag==0)
				break;
			follow_list1=follow_list1->nloc;
			}
		printf("	%d",flag);

                //code for the follow
                //head_parser_table=add_entry_to_table_with_follow(temp,temp2,follow_list,head_parser_table);
		if(flag==0){
			follow_list1=follow_list;
	                
	        	while(follow_list1!=NULL){
				head_p=head_parser_table;
				//printf(" %s",follow_list1->ch);
	        	        while(head_p!=NULL){
					flag=strcmp(head_p->ch, follow_list1->ch);
				//	printf("[%s]",head_p->ch);
					if(flag==0)
						break;
					head_p=head_p->nloc;
					}
				//while(head_p!=NULL){
				//	printf("%s",head_p->ch);
				//	head_p=head_p->nloc;
				//	}
	        	        node=(struct _parser_table*)malloc(sizeof(struct _parser_table ));
	        	        node->ch=temp->ch;
        		        node->nloc=temp2;
        		        node->down=NULL;
			
        		        if(head_p->down==NULL)
        		        	head_p->down=node;
        		        else{
        		                loop_count=head_p->down;
        		                while(loop_count->down!=NULL)
        		                      loop_count=loop_count->down;
					
        		                loop_count->down=node;
        		                }
				
        	        	follow_list1=follow_list1->nloc;
                		}
			}
                }
	else{
		first_list1=first_list;

		while(first_list1!=NULL){
			while(strcmp(first_list1->ch, head_p->ch))
				head_p=head_p->nloc;
			
		        node=(struct _parser_table*)malloc(sizeof(struct _parser_table ));
		        node->ch=temp->ch;
		        node->nloc=temp2;
		        node->down=NULL;
			
		        if(head_p->down==NULL)
		                head_p->down=node;
			else{
				loop_count=head_p->down;
				while(loop_count->down!=NULL)
					loop_count=loop_count->down;

				loop_count->down=node;
				}
                	first_list1 = first_list1->nloc;
                	}
		}
        return(head_parser_table);
}


int display_table(struct _table_head * head_parser_table)
{
	struct _parser_table * temp;
	struct _table_head *head_p;
	struct _p_end * loc;	

	head_p = head_parser_table;
	fputs("\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",log_fp);
	printf("\nFinal Parser Table:-\n");
	
	fputs("\nParser Table:",log_fp);

	if(head_parser_table==NULL)
		printf("\n List is empty");
	else{
		while(head_p!=NULL){
			printf(" \n%s: ", head_p->ch);
			fprintf(log_fp,"\n%s: ",head_p->ch);

			temp=head_p->down;
			if(temp!=NULL){
				while(temp!=NULL){
					printf("	[%s:", temp->ch);
					fprintf(log_fp,"	[%s:", temp->ch);
					loc=temp->nloc;
					if(loc!=NULL){
						while(loc!=NULL){
							printf("%s",loc->ch);
							fprintf(log_fp,"%s",loc->ch);
							loc=loc->nloc;
							}
						printf("]");
						fputs("]",log_fp);
						}
					temp=temp->down;
					}
				}
			head_p=head_p->nloc;
			}
		}
return(1);
}


