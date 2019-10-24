#include<stdio.h>
#include<stdlib.h>
#include "header.h"
#include<string.h>

int generate_itemset(struct _start * head)
{
	struct _start *temp, *head1, *node, *r;
	struct _p_start *temp1, *node1, *s;	
	struct _p_end *temp2, *node2, *t;
	struct _i_start * I;	

	temp=head;
	head1=NULL;
	if(head==NULL)
		printf("\n List Is Empty");
	else{	
		printf("\n////////////////////////////////////////////////////////////////////////////");
		
		printf("\nGrammer IS:-");
		while(temp!=NULL){
			node=(struct _start *)malloc(sizeof(struct _start));
			node->nloc=NULL;
			node->down=NULL;
			node->ch=temp->ch;
			if(head1==NULL)
				head1=node;
			else{
				r=head1;
				while(r->down!=NULL)
					r=r->down;
				
				r->down=node;
				}
			
			printf("\n%s:",temp->ch);
			temp1=temp->nloc;

			while(temp1!=NULL){
				node1=(struct _p_start *)malloc(sizeof(struct _p_start));
	                        node1->nloc=NULL;
        	                node1->down=NULL;

				if(node->nloc==NULL)
					node->nloc=node1;
				else{
					s=node->nloc;
					if(s->down!=NULL)
						s=s->down;

					s->down=node1;
					}
				temp2=temp1->nloc;
///////////
				while(temp2!=NULL){
					node2=(struct _p_end *)malloc(sizeof(struct _p_end));
        	                        node2->nloc=NULL;
					node2->ch=temp2->ch;

                	                if(node1->nloc==NULL)
                	                        node1->nloc=node2;
                        	        else{
                                	        t=node1->nloc;
                                	        if(t->nloc!=NULL)
                                        		t=t->nloc;
                                        	t->nloc=node2;
                                        	}
					printf("%s",temp2->ch);
					temp2=temp2->nloc;
					}
				printf("|");
				temp1=temp1->down;
				}

			temp=temp->down;
			}
		}
	tt(head1);
	I=first_item_set(head);
	item_set(I,head);
return(1);
}

int item_set(struct _i_start * I, struct _start * head)
{
	struct _i_start * I1, *r;
	struct _start * temp;
	struct _p_start * temp1;
	struct _dot_start * node1;
	struct _p_end * temp2, * node2, *s ;
	char *h;	
	
	I1=NULL;
	temp=head;
	h=I->ch;
	printf("\n %s",h);
	
	while( strcmp(h,temp->ch))
		temp=temp->down;
	
	temp1=temp->nloc;
	
	while(temp1!=NULL){
		node1=(struct _dot_start *)malloc(sizeof(struct _dot_start));
		node1->down=NULL;
		node1->nloc=NULL;
		node1->dot=1;

		if(I1==NULL)
			I1->nloc=node1;
		else{
			r=I1;
			while(r->down!=NULL)
				r=r->down;
			r->nloc=node1;
			}
		temp2 = temp1->nloc;
		while(temp2!=NULL){
			node2=(struct _p_end*)malloc(sizeof(struct _p_end));
			node2->nloc=NULL;
			node2->ch=temp2->ch;

			if(node1->nloc==NULL)
				node1->nloc=node2;
			else{
			        s=node2;
				while(s->nloc!=NULL)
					s=s->nloc;
				s->nloc=node2;
				}
			temp2=temp2->nloc;
			}

		temp1=temp1->down;
		}
	printf("\n %s",h);
}

struct _i_start * first_item_set(struct _start * head)
{
	struct _i_start *I, * node;
	struct _dot_start * node1; 
	struct _p_end * node2;
	char *h,*h2 ;
	
	fflush(stdout);
	printf("\nhiiiiiiii");
	h=head->ch;
	printf("\n %s",h);

	//strcat(h,"1");
	node=(struct _i_start *)malloc(sizeof(struct _i_start ));
	node->ch=h;
	node->nloc=NULL;
	node->down=NULL;
	
	I = node;
	
	node1=(struct _dot_start *)malloc(sizeof(struct _dot_start ));
	node1->dot=1;
	node1->nloc=NULL;
	node1->down=NULL;
	
	I->nloc = node1;
	
	node2=(struct _p_end *)malloc(sizeof(struct _p_end ));
	node2->ch=head->ch;
	node2->nloc=NULL;

	node1->nloc=node2;

	printf("\nFirst Item Set:");
	printf("\n %s:",I->ch);
	printf("%d  %s",node1->dot,node2->ch);
	
return(I);
}

int tt(struct _start * head1)
{
	struct _start *temp, *node, *r;
        struct _p_start *temp1, *node1, *s;
        struct _p_end *temp2, *node2, *t;

        temp=head1;
        if(head1==NULL)
                printf("\n List Is Empty");
        else{
                printf("\n////////////////////////////////////////////////////////////////////////////");

                printf("\nhead1 Grammer IS:-");
                while(temp!=NULL){

                        printf("\n%s:",temp->ch);
                        temp1=temp->nloc;

                        while(temp1!=NULL){
                                temp2=temp1->nloc;
				while(temp2!=NULL){
                                        printf("%s",temp2->ch);
                                        temp2=temp2->nloc;
                                        }
                                printf("|");
                                temp1=temp1->down;
                                }
                        temp=temp->down;
                        }
                }
                                       
return(1);
}

