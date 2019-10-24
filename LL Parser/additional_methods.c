#include<stdio.h>
#include<stdlib.h>
#include "header.h"

struct _start_follow * remove_repetative_symbols(struct _start_follow * head_follow)
{	
	struct _start_follow * head_follow1;
	struct _p_end * first_list;
	struct _p_end * follow_list;

	head_follow1=head_follow;
	printf("\nHere in the redundancy removal function "); 
	while(head_follow1!=NULL){
		first_list=head_follow1->ploc;
		follow_list=head_follow1->nloc;
		printf("\n%s	",head_follow1->ch);
		first_list=remove_symbols(first_list);
		printf(" , ");
		follow_list=remove_symbols(follow_list);

		head_follow1=head_follow1->down;
		}
	return(head_follow);
}

struct _p_end * remove_symbols(struct _p_end * f_list)
{
	struct _p_end * temp, *temp1, *ploc_temp;
	int flag=0;

	temp=f_list;
	while(temp!=NULL){
		//printf("%s",temp->ch);
		ploc_temp=temp;
		temp1=temp->nloc;

		while(temp1!=NULL){
			flag=strcmp(temp->ch,temp1->ch);
			fflush(stdout);
			printf(" [ %s %s %d ] ",temp->ch,temp1->ch,flag);
			if(flag==0)
				f_list=delete_node(f_list, ploc_temp);
			ploc_temp=temp1;

			temp1=temp1->nloc;
			}
		temp=temp->nloc;
		}
	return(f_list);
}

struct _p_end * delete_node(struct _p_end * f_list, struct _p_end * p_temp)
{
	struct _p_end * temp, *n_temp;;	
	
	temp = p_temp->nloc;
	n_temp=temp->nloc;
	//printf("	%s %s",p_temp->ch,temp->ch);
	
	if(n_temp == NULL)
		p_temp->nloc=NULL;
	else{
		p_temp->nloc=n_temp;
		}
	//free(temp);
	
	return(f_list);
}

int traversal1(struct _start * head)
{
	struct _start *temp;
	struct _p_start *temp1;	
	struct _p_end *temp2;
	
	temp=head;
	if(head==NULL)
		printf("\n List Is Empty");
	else{	
		printf("\n////////////////////////////////////////////////////////////////////////////");

		fputs("\nHere Grammer Represent Through The Linked List Stored in The Memory: ",log_fp);
		while(temp->down!=NULL){
			fprintf(log_fp,"\n%s:",temp->ch);
			temp1=temp->nloc;
			while(temp1->down!=NULL){
				temp2=temp1->nloc;
				while(temp2->nloc!=NULL){
					fprintf(log_fp,"%s",temp2->ch);
					temp2=temp2->nloc;	
					}
				fprintf(log_fp,"%s",temp2->ch);
				fputs("|",log_fp);
				temp1=temp1->down;
				}
				temp2=temp1->nloc;
                                while(temp2->nloc!=NULL){
					fprintf(log_fp,"%s",temp2->ch);
                                        temp2=temp2->nloc;
                                        }
				fprintf(log_fp,"%s",temp2->ch);
				fprintf(log_fp,"|");
				temp=temp->down;
			}
			fprintf(log_fp,"\n%s:",temp->ch);
                        temp1=temp->nloc;
                        while(temp1->down!=NULL){                               
                               temp2=temp1->nloc;
                               while(temp2->nloc!=NULL){
					fprintf(log_fp,"%s",temp2->ch);
                                        temp2=temp2->nloc;
                                        }               
			       fprintf(log_fp,"%s",temp2->ch);
			       fputs("|",log_fp);
                               temp1=temp1->down;
                               }   
				temp2=temp1->nloc;
                                while(temp2->nloc!=NULL){
					fprintf(log_fp,"%s",temp2->ch);;
                                        temp2=temp2->nloc;
                                        }
				fprintf(log_fp,"%s",temp2->ch);
				fputs("|",log_fp);

		}//main else
		//printf("\n");
return(1);
}

int first_follow_display1(struct _start_follow * head_follow)
{
	struct _start_follow *f, *f1;
        struct _p_end  *t1;

        fflush(stdout);
        fputs("\n",log_fp);
        f=head_follow;
	fputs("\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",log_fp);
	fputs("\nFollow list of Grammer",log_fp);
        fputs("\nStarting sym:\tFollow List-",log_fp);
        while(f!=NULL){
                fprintf(log_fp,"\n%s :-\t\t ", f->ch);
                t1=f->nloc;
                if(t1==NULL)
                        printf("empty");
                else{
                        while(t1!=NULL){
                                fprintf(log_fp,"%s  ",t1->ch);
                                t1=t1->nloc;
                                }
                        }
                f=f->down;
                }
        printf("\n");
return(1);
}

int  travers1( struct _p_end * head_terminal)
{
        struct _p_end *temp;
        temp=head_terminal;

        fflush(stdout);
	fputs("\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",log_fp);
        if(temp==NULL)
                printf("\nList Is Empty");
        else{
                fprintf(log_fp,"\n Here is the list of terminal symbol:");
                while(temp->nloc!=NULL){
                        fprintf(log_fp,"\n %s",temp->ch);
                        temp=temp->nloc;
                        }
                printf(" %s",temp->ch);
                }
return(1);
}

