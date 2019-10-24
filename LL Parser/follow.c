#include  "header.h"

struct _start_follow * follow ( struct _start * head, struct _p_end ** head1 ) 
{
	struct _start *temp, *ttemp, *tttemp, *tempp;
	struct _start_follow *head_follow, *f, *node, *t;
	struct _start *head_follow1;
	struct _p_end *t1;
	int i,j,k=0;

	temp=head;
	head_follow=NULL;
	i=0;
	j=2;
	fflush(stdout);
	printf("\n\n////////////////////////////////////////////////////////////////////////////");
	printf("\nHERE IN THE FOLLOW FUNCTION");

	head_follow1=head;
	while(head_follow1!=NULL){
		
		node=(struct _start_follow*)malloc(sizeof(struct _start_follow));
		node->ch=head_follow1->ch;
		node->down=NULL;
		node->nloc=NULL;
		node->ploc=NULL;	

		if(head_follow==NULL)
			head_follow=node;
		else{
			t=head_follow;
			while(t->down!=NULL)
				t=t->down;
			t->down=node;	
			}
		head_follow1=head_follow1->down;
		}

	f=head_follow;
        while(f!=NULL){
			f->ploc=*head1;			
		head1++;
                f=f->down;
                }
		
	first_follow_display(head_follow);
	tempp=temp;
	ttemp=temp;
	tttemp=temp;	

/* 	for first rule of follow	*/
/*	for the grammer of type A->aBb	*/
	
	printf("\n ////////////////////////////case 2 starts");	
	while(temp->down!=NULL){
		head_follow=create_follow_list_case_1(head, temp, head_follow);
		temp=temp->down;
		}
	head_follow=create_follow_list_case_1(head, temp, head_follow);

	first_follow_display(head_follow);

/*	for second rule of follow	*/
/*	for the grammer of type A->aB   */
	
	while(k<2){
	ttemp=tempp;
	printf("\n //////////////////////////////case 2 starts");
	while(ttemp->down!=NULL){
                head_follow=create_follow_list_case_2(head, ttemp, head_follow);
                ttemp=ttemp->down;
                }
        head_follow=create_follow_list_case_2(head, ttemp, head_follow);

        first_follow_display(head_follow);

/*	calling for the third case of the follow			*/
/*	for the grammer of type A->aBb where first of b contains null	*/
	printf("\n ///////////////////////////////case 3 starts");
	tttemp=tempp;
	while(tttemp->down!=NULL){
                head_follow=create_follow_list_case_3(head, tttemp, head_follow);
                tttemp=tttemp->down;
                }
        head_follow=create_follow_list_case_3(head, tttemp, head_follow);
	
        first_follow_display(head_follow);

	k++;
	}
	printf("\n");
return(head_follow);
}

struct _start_follow * create_follow_list_case_2(struct _start *head , struct _start *temp, struct _start_follow *head_follow)
{
        struct _p_end *node;
        struct _p_start *temp1, *temp11;
        struct _p_end *temp2, *d;
        int i, flag, j;

        i=0;
        flag=0;

        temp1=temp->nloc;
        //loop for making movement between different production rule of a single non terminal symbol 
        while(temp1!=NULL){
                temp2=temp1->nloc;
                printf("\n%s :",temp->ch);

                //for checking the case first in the follow case
                head_follow=follow_case2(head,temp, head_follow, temp2);

                temp1=temp1->down;
                }

return(head_follow);
}

struct _start_follow * follow_case2(struct _start * head, struct _start *temp, struct _start_follow *head_follow, struct _p_end *temp2)
{
        struct _p_end * temp22, * temp221;
        int i, flag, j;
        struct _start_follow *f;
	struct _start *temp11, *t;

        temp22=temp2;
        j=0;
        i=0;
        flag=0;
        f=NULL;
	
	while(temp22!=NULL){
		printf("%s",temp22->ch);
		temp22=temp22->nloc;
		}

        temp22=temp2;
	flag=check_for_nonterminal(head,temp22);
        if(flag!=0){
        	printf("        nonterminal symbol not found");
                return(head_follow);
                }
        else{
		temp22=temp2;
		while(temp22->nloc!=NULL)
			temp22=temp22->nloc;
		
		printf("	:%s %s",temp->ch,temp22->ch);

		flag=0;
		t=head;
		while(t->down!=NULL){
			flag=strcmp(t->ch,temp22->ch);
			if(flag==0)
				break;
			t=t->down;
			}
		flag=strcmp(t->ch,temp22->ch);
                        
		if(flag!=0){
			printf("	Not possible becouse no any nonterminal symbol at last");
			return(head_follow);
			}
		else{
			flag=strcmp(temp->ch,temp22->ch);
			if(flag==0){
				printf("	same nonterminal are present");
				return(head_follow);
				}
			else{
				head_follow = add_follow_set(temp, temp22, head_follow);
				}
			}
		}
                
return(head_follow);
}

struct _start_follow * add_follow_set(struct _start *temp, struct _p_end *temp22, struct _start_follow *head_follow)
{
	struct _start_follow * head_follow1;
	struct _p_end * a_follow, * b_follow ,* loop_counter, *node ,*a , *b; 
	int flag;
	
	flag=0;
	head_follow1=head_follow;
	a_follow=NULL;
	b_follow=NULL;	

	printf("	%s %s",temp->ch,temp22->ch);
	//////////////////////////////////////////////
	while( strcmp( head_follow1->ch, temp->ch ))
		head_follow1=head_follow1->down;
	
	a=head_follow1->nloc;
	
	while(a!=NULL){
		node=(struct _p_end*)malloc(sizeof(struct _p_end ));
		node->ch=a->ch;
		node->nloc=NULL;
		if(a_follow==NULL)
			a_follow=node;
		else{
			loop_counter=a_follow;
			while(loop_counter->nloc!=NULL)
				loop_counter=loop_counter->nloc;

			loop_counter->nloc=node;
			}
		a=a->nloc;
		}
	loop_counter=a_follow;
	while(loop_counter!=NULL){
		printf("%s",loop_counter->ch);
		loop_counter=loop_counter->nloc;
		}
	///////////////////////////////////////////////
	
	head_follow1=head_follow;
	while( strcmp( head_follow1->ch, temp22->ch ))
                head_follow1=head_follow1->down;

        if(head_follow1->nloc==NULL)
		head_follow1->nloc=a_follow;
	else{
		b_follow=head_follow1->nloc;
	
        	while(b_follow->nloc!=NULL)
			b_follow=b_follow->nloc;
		
		b_follow->nloc=a_follow;
		}
	
	printf("	kaam ho gaya ");
return(head_follow);
}

struct _start_follow * create_follow_list_case_3(struct _start *head , struct _start *temp, struct _start_follow *head_follow)
{
	struct _p_end *node;
        struct _p_start *temp1, *temp11;
        struct _p_end *temp2, *d;
        int i, flag, j;

        i=0;
        flag=0;

        temp1=temp->nloc;
        //loop for making movement between different production rule of a single non terminal symbol 
        while(temp1!=NULL){
                temp2=temp1->nloc;
                printf("\n%s :",temp->ch);
                //for checking the case first in the follow case
                head_follow=follow_case3(head,temp, head_follow, temp2);
                temp1=temp1->down;
                }

	return(head_follow);
}

struct _start_follow * follow_case3(struct _start * head, struct _start *temp,  struct _start_follow * head_follow, struct _p_end *temp2)
{
        struct _p_end * temp22, *temp221, *temp222;
        int i, flag, j;
        struct _start_follow *f;
        struct _start *temp11;
	struct _start_follow * head_follow1;

        temp22=temp2;
        j=0;
        i=0;
        flag=0;
        f=NULL;

        while(temp22!=NULL){
		printf("%s",temp22->ch);
                i++;
                temp22=temp22->nloc;
                }
        printf("        :%d",i);

        if(i<=1){
                printf("        follow not possible becouse of single element in production rule");
                return(head_follow);
                }
        else{
                temp22=temp2;
                flag=check_for_nonterminal(head,temp22);
                if(flag!=0){
                        printf("        nonterminal symbol not found");
                        return(head_follow);
                        }
                else{
                        flag=check_for_posion_of_nonterminal(head,temp22);
                        if(flag==i){
                                printf("        %d      follow not possible in the case becouse their is starting symbol at the last means beta=null",flag);
                                return(head_follow);
                                }
                        else{
				printf("        %d",flag);
                                printf("        %s",temp22->ch);

                                while(j<(flag-1)){
                                        temp22=temp22->nloc;
                                        j++;
                                        }
                                printf("         :%s",temp22->ch);
				
				temp221=temp22->nloc;
				printf("	%s",temp221->ch);
	
				temp11=head;
				while(temp11!=NULL){
					flag=strcmp(temp11->ch,temp221->ch);
					if(flag==0)
						break;
					temp11=temp11->down;
					}
				printf("	%d",flag);

				if(flag==0){
					printf("done");
					head_follow1=head_follow;
					while(strcmp(head_follow1->ch, temp221->ch))
						head_follow1=head_follow1->down;
					
					//printf("%s",head_follow1->ch);
					if(head_follow1->ploc!=NULL){
						temp222=head_follow1->ploc;
						
						while(temp222!=NULL){
							flag=strcmp("@",temp222->ch);
							if(flag==0)
								break;
							
							temp222=temp222->nloc;
							}
						printf("	%d",flag);
						if(flag==0)
							head_follow = add_follow_set(temp, temp22, head_follow);
						}
					}
				
                                temp22=temp22->nloc;
                                printf("        :%s",temp22->ch);
				if(temp22->nloc!=NULL)
	                              head_follow=follow_case3(head,temp,head_follow, temp22);
				}
			}
		}

return(head_follow);
}



struct _start_follow * create_follow_list_case_1(struct _start *head , struct _start *temp , struct _start_follow *head_follow)
{	
	struct _p_end *node;
	struct _p_start *temp1, *temp11;
	struct _p_end *temp2, *d;
	int i, flag, j;
	
	i=0;
	flag=0;
	
	//for adding the $ in the starting symbol follow list	
	if(!strcmp(head->ch,temp->ch)){
		node=(struct _p_end*)malloc(sizeof(struct _p_end));
		node->ch="$";
		node->nloc=NULL;
	
		head_follow->nloc=node;
		}

	//loop for making movement between different production rule of a single non terminal symbol 
	temp1=temp->nloc;
	while(temp1!=NULL){
		temp2=temp1->nloc;		
		printf("\n%s :",temp->ch);

		//for checking the case first in the follow case
		head_follow = follow_case1(head, head_follow, temp2);

		temp1 = temp1->down;
		}
return(head_follow);
}


struct _start_follow * follow_case1(struct _start * head, struct _start_follow * head_follow, struct _p_end *temp2)
{
	struct _p_end * temp22, *temp221;
	int i, flag, j;
	struct _start_follow *f;
	struct _start *temp11;	

	temp22=temp2;
	j=0;
	i=0;
	flag=0;
	f=NULL;

	while(temp22!=NULL){
		i++;
		printf("%s",temp22->ch);
		temp22=temp22->nloc;
		}	
	printf("        :%d",i);

	if(i<=1){
		printf("	follow not possible becouse of single element in production rule");
		return(head_follow);
		}
	else{
		temp22=temp2;		
		flag=check_for_nonterminal(head,temp22);
		if(flag!=0){
			printf("	nonterminal symbol not found");
			return(head_follow);
			}
		else{
			flag=check_for_posion_of_nonterminal(head,temp22);
			if(flag==i){
				printf("	%d	follow not possible in the case becouse their is starting symbol at the last means beta=null",flag);
				return(head_follow);
				}
			else{
				printf("	%d",flag);
				printf("	%s",temp22->ch);
				
				while(j<(flag-1)){
					temp22=temp22->nloc;
					j++;
					}
				printf("	 :%s",temp22->ch);
				
				head_follow=calculate_first(head, head_follow, temp22);
				temp22=temp22->nloc;
				printf("	:%s",temp22->ch);
				if(temp22->nloc!=NULL)
					head_follow=follow_case1(head, head_follow, temp22);
				}
			}
		}
return(head_follow);
}


struct _start_follow * calculate_first(struct _start *head , struct _start_follow *head_follow, struct _p_end * temp22)	
{
	struct _start * temp;
	struct _p_end *temp221, *temp222, *node, *t_head, *t, *p;
	struct _start_follow *head_follow1, *head_follow2;
	int flag;
	
	flag=0;
	head_follow1=head_follow;	
	temp=head;
	t_head=NULL;

	printf("        %s",temp22->ch);
        temp221=temp22->nloc;
	printf("%s",temp221->ch);


	while(strcmp(head_follow1->ch,temp22->ch )){
		head_follow1=head_follow1->down;
		}

	temp222=head_follow1->nloc;
	
	if(temp222!=NULL){
		while(temp222->nloc!=NULL)
			temp222=temp222->nloc;
		}

	while(temp!=NULL){
		flag=strcmp(temp221->ch, temp->ch);
		if(flag==0)
			break;
		temp=temp->down;
		}
	
	printf("	%d",flag);

	if(flag!=0){
		node=(struct _p_end*)malloc(sizeof(struct _p_end));
		node->ch=temp221->ch;
		node->nloc=NULL;
		
		if(temp222==NULL)
			head_follow1->nloc=node;
		else
			temp222->nloc=node;
		}
	else{
		head_follow2=head_follow;
		while(strcmp(head_follow2->ch,temp221->ch ))
			head_follow2=head_follow2->down;

		printf("	=%s",head_follow2->ch);

		t=head_follow2->ploc;
		
		while(t!=NULL){
			if(strcmp("@",t->ch)){ 
				printf("%s",t->ch);
				node=(struct _p_end*)malloc(sizeof(struct _p_end));
		               	node->ch=t->ch;
                		node->nloc=NULL;
				
				if(t_head==NULL)
					t_head=node;
				else{
					p=t_head;
					while(p->nloc!=NULL)
						p=p->nloc;
			
					p->nloc=node;
					}
				}
				t=t->nloc;
					
			}
			
		if(temp222==NULL)
			head_follow1->nloc=t_head;
		else
			temp222->nloc=t_head;
		}

return(head_follow);
}


int check_for_posion_of_nonterminal(struct _start *temp,struct _p_end * temp22)
{
	struct _start *temp1;	
	int flag=0,i=0;

	while(temp22!=NULL){
		i++;
		temp1=temp;
		while(temp1!=NULL){
			flag=strcmp(temp1->ch,temp22->ch);
			if(flag==0)
				break;
			temp1=temp1->down;
			}
		if(flag==0)
			break;
		temp22=temp22->nloc;
		}
	return(i);
}

int check_for_nonterminal(struct _start *temp, struct _p_end *temp22)
{
	int flag=0;
	struct _start *temp1;

	while(temp22!=NULL){
		temp1=temp;
		while(temp1!=NULL){
			flag=strcmp(temp1->ch,temp22->ch);
			if(flag==0)
				break;

			temp1=temp1->down;
			}
		if(flag==0)
			break;
		temp22=temp22->nloc;
		}
	return(flag);
}


int first_follow_display(struct _start_follow * head_follow)
{
	struct _start_follow *f, *f1;
	struct _p_end  *t1;	

	fflush(stdout);
	printf("\n");
	f=head_follow;
        printf("\nStarting sym:\tFirst List\tFollow List-");
        while(f!=NULL){
                printf("\n%s :-\t\t ", f->ch);
                t1=f->ploc;
		if(t1==NULL)
			printf("empty");
		else{	
                	while(t1!=NULL){
                        	printf("%s  ",t1->ch);
                        	t1=t1->nloc;
                        	}
			}
		printf("\t\t");	
		t1=f->nloc;
		if(t1==NULL)
			printf("empty");
		else{
			while(t1!=NULL){
				printf("%s  ",t1->ch);
				t1=t1->nloc;
				}	
			}
                f=f->down;
                }
	printf("\n");
return(1);
}

int follow_list_display(struct _start * temp, struct _start_follow * head_follow)
{
	struct _start_follow *head_follow2;

	printf("\nFollow List Of %s:",temp->ch);
	if(head_follow==NULL)
		printf("empty");
	else{
		head_follow2=head_follow;
		while(head_follow2->down!=NULL){
			printf("%s",head_follow2->ch);
			head_follow=head_follow2->down;
			}
		printf("%s",head_follow2->ch);
		}
return(1);
}
