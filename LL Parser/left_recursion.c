#include<stdio.h>
#include<stdlib.h>
#include "header.h"

struct _start * left_recursion(struct _start * head)
{
	struct _start * temp;
	struct _p_start * temp1, * temp11;	
	struct _p_end * temp2;
	int flag=0,i=0;

	printf("\n Hello");

	temp=head;
	while(temp!=NULL){
		temp1=temp->nloc;
		while(temp1!=NULL){
			temp2=temp1->nloc;
			flag=strcmp(temp2->ch, temp->ch);
			if(flag==0)
				break;
			temp1=temp1->down;
			}
		if(flag==0)
			break;
		temp=temp->down;
		}
	if(flag!=0){
		printf("\n Grammer is not recursive");
		return(head);
		}
	else{
		printf("\n Grammer is recursive");
		temp=head;
		while(temp!=NULL){
			temp1=temp->nloc;
			while(temp1!=NULL){
				flag=0;
				temp2 = temp1->nloc;
				flag=strcmp(temp2->ch, temp->ch);
				if(flag==0){
					i=0;
					temp11=temp->nloc;	
					while(temp11!=NULL){
						i++;
						temp11=temp11->down;
						}
					printf("\n %d",i);
					if(i<2){
						printf("\nThe Grammer is not LL grammer");
						exit (0);	
						}
					}

				temp1=temp1->down;	
				}

			temp=temp->down;
			}
		
		printf("\n Grammer is LL grammer");

		temp=head;
		while(temp!=NULL){
			temp1=temp->nloc;
			while(temp1!=NULL){
				flag=0;
				temp2=temp1->nloc;
				flag=strcmp(temp->ch,temp2->ch);
				if(flag==0)
					head=find_next_nonrecursive(head,temp,temp1);
				temp1=temp1->down;
				}
			temp=temp->down;
			}
		}

	printf("\n");
	return(head);
}

struct _start * find_next_nonrecursive(struct _start *head, struct _start * temp, struct _p_start * temp1)
{
	struct _p_start * temp11;
	struct _p_end * temp2, *second_p_list, *first_p_list ,*fpl, *node, *f, *temp22;
	int flag=0;
	char *ch1[5]={"G","H","I","J","K"};
	static int i=0;
	
        temp22=temp1->nloc;
	//temp11=temp1->down;
	temp11=temp->nloc;
	first_p_list=NULL;	
	second_p_list= NULL;

	while(temp11!=NULL){
		temp2=temp11->nloc;
		flag=strcmp(temp2->ch, temp->ch);
		if(flag!=0)
			break;	
		temp11=temp11->down;
		}
	if(temp11!=NULL){
		//printf("\n	%s	%s",temp22->ch, temp2->ch);
		temp2=temp1->nloc;
		printf("\n\nGrammer which is recursive: ");
		while(temp2!=NULL)
			{
			printf("%s",temp2->ch);
			temp2=temp2->nloc;
			}

		temp22=temp11->nloc;
		printf("\nGrammer which is solution of recursive grammer: ");
		while(temp22!=NULL){
			printf("%s",temp22->ch);
			temp22=temp22->nloc;
			}

		/////////////////////////////////////////////

		fpl=temp11->nloc;
		//fpl=first_p_list;
		while(fpl!=NULL){
			node=(struct _p_end*)malloc(sizeof(struct _p_end));
	                node->ch=fpl->ch;
	                node->nloc=NULL;
			
			if(first_p_list==NULL)
				first_p_list=node;
			else{
				f=first_p_list;
				while(f->nloc!=NULL)
					f=f->nloc;
				f->nloc=node;
				}
			fpl=fpl->nloc;
			}

		node=(struct _p_end*)malloc(sizeof(struct _p_end));
		node->ch=ch1[i];
		node->nloc=NULL;
		
		fpl=first_p_list;
		while(fpl->nloc!=NULL)
			fpl=fpl->nloc;
		fpl->nloc=node;

		fpl=first_p_list;
		
		printf("\nGrammer to be added on behalf of recursive grammer: ");
		while(fpl!=NULL){
			printf("%s",fpl->ch);
			fpl=fpl->nloc;
			}
		
		//////////////////////////////////////////////	
		fpl=temp1->nloc;
		fpl=fpl->nloc;

		while(fpl!=NULL){
			node=(struct _p_end*)malloc(sizeof(struct _p_end));
			node->ch=fpl->ch;
			node->nloc=NULL;
			
			if(second_p_list==NULL)
				second_p_list=node;
			else{
				f=second_p_list;
				while(f->nloc!=NULL)
					f=f->nloc;

				f->nloc=node;		
				}	
			fpl=fpl->nloc;
			}

		node=(struct _p_end*)malloc(sizeof(struct _p_end));
		node->ch=ch1[i];
		node->nloc=NULL;

		fpl=second_p_list;
		while(fpl->nloc!=NULL)
			fpl=fpl->nloc;

		fpl->nloc=node;
		
		printf("\nGrammer that generated intermediately: ");
		
		fpl=second_p_list;
                while(fpl!=NULL){
                        printf("%s",fpl->ch);
                        fpl=fpl->nloc;
                        }

		/* 	first_p_list and temp11
		   	second_p_list and temp1
		   	contains the two list
		*/
		head=add_another_non_terminal(head, second_p_list, ch1[i]);
		head=remove_recursive_grammer(head, temp, temp1 ,temp11 ,first_p_list);
		
		//traversal(head); 
		i=i+1;
		}
	return(head);
}

struct _start* remove_recursive_grammer(struct _start *head, struct _start *temp, struct _p_start *temp1, struct _p_start *temp11, struct _p_end * first_p_list)
{	
	struct _p_end * temp2;
	struct _p_start * temp111, *ploc_temp111, *nloc_temp111;	
	int flag=0;

	printf("\n");
	temp2=temp1->nloc;
	while(temp2!=NULL){
		printf("%s",temp2->ch);
		temp2=temp2->nloc;
		}
	printf("\n");
	temp2=temp11->nloc;
	while(temp2!=NULL){
		printf("%s",temp2->ch);
		temp2=temp2->nloc;
		}
	printf("\nYesssssssssss");

	temp1->nloc = first_p_list;
	
	if(temp11->down==NULL){
		temp111=temp->nloc;
		ploc_temp111=temp111;

		while(temp111->down!=NULL){
			if(temp111==temp11)
				break;
			ploc_temp111=temp111;
			temp111=temp111->down;
			}
		ploc_temp111->down=NULL;
		free(temp11);
		}
	else{
		temp111=temp->nloc;
		ploc_temp111=temp111;
		nloc_temp111=temp111->down;

		while(temp111->down!=NULL){
			if(temp111==temp11)
				break;
			ploc_temp111=temp111;
			temp111=temp111->down;
			nloc_temp111=temp111->down;
			}
		if(temp111==temp->nloc)
			temp->nloc=nloc_temp111;
		else{
			ploc_temp111->down=nloc_temp111;
			}	
		}
	return(head);
}

struct _start* add_another_non_terminal(struct _start *head, struct _p_end * second_p_list, char * ch)
{	
	struct _start * node, *tempp;
	struct _p_start *temp111, *temp112;
	struct _p_end * temp2;	

	printf("\nHellooooooooo %s",ch);
	
	node=(struct _start*)malloc(sizeof(struct _start));
	node->ch=ch;
	node->down=NULL;
	node->nloc=NULL;	

	tempp=head;
	while(tempp->down!=NULL)
		tempp=tempp->down;
	
	tempp->down=node;
	
	temp111=(struct _p_start*)malloc(sizeof(struct _p_start));
	temp111->nloc=NULL;
	temp111->down=NULL;
	
	tempp=node;
	tempp->nloc=temp111;
	
	temp111->nloc=second_p_list;
	
	temp112=(struct _p_start *)malloc(sizeof(struct _p_start));
        temp112->nloc=NULL;
        temp112->down=NULL;
	
	temp111->down=temp112;

	temp2=(struct _p_end*)malloc(sizeof(struct _p_end));
	temp2->ch="@";
	temp2->nloc=NULL;
	
	temp112->nloc=temp2;
	
	return(head);
}
