#include "header.h"

struct _start_follow * first(struct _start *head)
{
	struct _start *temp;
	struct _p_end *head_first, *head1[5];
	struct _start_follow *head_follow;
	int i=0,j;
	
	printf("\n\n////////////////////////////////////////////////////////////////////////////");
	fputs("\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",log_fp);
	printf("\nHERE IN THE FIRST FUNCTION:-");
	fputs("\nHere In The First Function:-",log_fp);	
	temp=head;

	while(temp->down!=NULL){
		head_first=NULL;
		head_first=create_first_list(head,temp,head_first);
		first_list_display(temp,head_first);
		head1[i]=head_first;
		i++;
		temp=temp->down;
	}
	head_first=NULL;
	head_first=create_first_list(head,temp,head_first);
	first_list_display(temp,head_first);
	head1[i]=head_first;

	j=0;
	/*while(j<=i){
		first_list_display(temp,head1[j]);
		j++;
		}*/
//	printf("\n");
//	traversal(head);
	head_follow=follow(head,head1);
//	first_follow_display(head_follow);	
	
return(head_follow);
}
	
struct _p_end *create_first_list(struct _start *head, struct _start *temp, struct _p_end *head_first)
{
	struct _p_start *temp1;
	struct _p_end *temp2;
	struct _start *head1;
	int flag;

	flag=0;
	temp1=temp->nloc;

	while(temp1!=NULL){
		head1=head;
		temp2=temp1->nloc;

		while(head1->down!=NULL){
			flag=strcmp(head1->ch,temp2->ch);
			if(flag==0)
				break;
			head1=head1->down;
			}
		flag=strcmp(head1->ch,temp2->ch);

		if(flag!=0)
			head_first=add_node_to_list(head_first,temp2);
		else{
			flag=strcmp(temp->ch,head1->ch);
			
			if(flag!=0){
				head_first=create_first_list(head,head1,head_first);
				//first_list_display(temp,head_first);
				}
			}
		temp1=temp1->down;
		}
return(head_first);
}

struct _p_end *add_node_to_list(struct _p_end *head_first, struct _p_end *temp2)
{
	struct _p_end *temp, *node;

	node=(struct _p_end *)malloc(sizeof(struct _p_end));
                        node->ch=temp2->ch;
                        node->nloc=NULL;
        if(head_first==NULL)
        	head_first=node;
        else{
        	temp=head_first;
                while(temp->nloc!=NULL)
                	temp=temp->nloc;
                temp->nloc=node;
		}
	return(head_first);
}

int first_list_display(struct _start * temp1,struct _p_end * head_first)
{
	struct _p_end *temp;
	temp=head_first;
      
	printf("\nFirst List Of %s :",temp1->ch);   	
	fprintf(log_fp,"\n%s:-",temp1->ch);
	if(temp==NULL)
		printf("empty:");
	else{
		while(temp!=NULL){
			printf("%s,",temp->ch);
			fprintf(log_fp,"%s",temp->ch);
			temp=temp->nloc;
		}
	}
return(1);
}
