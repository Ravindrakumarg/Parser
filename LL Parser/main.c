#include "header.h"
 
int main()
{
	struct _start *head;
	struct _start_follow * head_follow;	
	struct _p_end * head_terminal;	
	struct _table_head * head_parser_table;
	//FILE * log_fp;

	head=NULL;
	head_terminal=NULL;	

	log_fp=fopen("log_grammer.txt","w");
	fputs("\tLog file for grammer parsing on different stage",log_fp);

	//removing the blank and tab spaces
	scan();
	
	//making the link list of starting symbols
        head=start_symbol_list(head);

	//display the starting symbol list
	display(head);

	//Making the linklist for the production rule of the grammer	
        head=linked_list(head);
	
	//for displaying the whole list
	traversal(head);
 	
	fputs("\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",log_fp);
	traversal1(head);

	//for making the lex file
	//make_lex_file(_fp);
		
	//for traversing in the terminal symbol list
	head_terminal=travers();
	
	//for removing the left recursion from the grammer
	head=left_recursion(head);	
	
	fputs("\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",log_fp);
	fputs("\n\nGrammer Represantation In the memory after removing  Left Recursion",log_fp);
	traversal1(head);

	//for the purpose of finding the first of the grammer
	head_follow=first(head);

	//for finding the follow set of the grammer
	//follow(head);
		
	//for removing the repetative symbols from the first follow list
	head_follow=remove_repetative_symbols(head_follow);
	
	//this function actuallu print the first follow of the grammer 
	first_follow_display(head_follow);

	first_follow_display1(head_follow);

	//call for making the parser table
	head_parser_table = create_parser_table( head, head_follow, head_terminal );

	//for generating the input file for further parsing
	generate_input_file(head,head_follow, head_terminal, head_parser_table);

	//
	process_input_parser_table(head, head_follow, head_terminal, head_parser_table);
	printf("\n");
return(0);	
}
