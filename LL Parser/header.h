#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

//#define EXIT_FAILURE 0
//#define EXIT_SUCCESS 1 
FILE * log_fp; 

/*for the single link node of the production rule*/
struct _p_end
{
	char *ch;
 	struct _p_end *nloc;
};

/*for the double link node of the production rule*/
struct _p_start
{
 	struct _p_start *down;
 	struct _p_end *nloc;
};

/*for the starting symbol of production rule*/
struct _start
{
	char *ch;
	struct _start *down;
 	struct _p_start *nloc;
};

/*for the purpose of storing node of first and follow*/
struct _start_follow
{
	char *ch;
	struct _start_follow *down;
	struct _p_end *nloc;			//for the follow set
	struct _p_end *ploc;  			//for the first set
};

/*for the pupose of storing the parser table */
struct _parser_table
{
	struct _parser_table *down;
	char *ch;
	struct _p_end *nloc;	
};

/*A data structure which points to the parser table */
struct _table_head
{
	struct _parser_table *down;
	char *ch;				//for non terminal
	struct _table_head * nloc;		//for production rule
};

//struct _p_end *head_end=NULL;

//scan function for removing the redundent blank,tan spaces from the input file
int scan();

//use to make the starting symbol list of production rule
struct _start * start_symbol_list(struct _start *);

//display the starting symbol link list
int display(struct _start *);

//Making the final linklist of the grammer
struct _start * linked_list(struct _start *);

//operation of link list 
struct _start *make_link_list(struct _start *,char *,char *,char );

//traversal of whole link list
int traversal(struct _start *);

//
int traversal1(struct _start *);

//for making the  lex file of the grammer
int make_lex_file(FILE *);

//for first of the grammer
int create_terminal_symbol(struct _start *, struct _p_end *);

//for traversing in the list
struct _p_end * travers();

//for finding the first of grammer
struct _start_follow * first(struct _start *);	

//
struct _p_end* create_first_list(struct _start *, struct _start *, struct _p_end *);

//
int first_list_display(struct _start *, struct _p_end *);

//
struct _start_follow * follow(struct _start *, struct _p_end **);

//
struct _start_follow * create_follow_list_case_1(struct _start *, struct _start *, struct _start_follow *);

//
struct _p_end* add_node_to_list(struct _p_end*, struct _p_end *);

//
int follow_list_display(struct _start *, struct _start_follow *);

//
struct _start_follow * follow_case1(struct _start *, struct _start_follow *, struct _p_end *);

//
int check_for_nonterminal(struct _start * , struct _p_end *);

//
int check_for_posion_of_nonterminal(struct _start *, struct _p_end *);

//
int first_follow_display(struct _start_follow * head_follow);

//
struct _start_follow * calculate_first(struct _start*, struct _start_follow *, struct _p_end *);

//
struct _start_follow * follow_case2(struct _start * , struct _start *, struct _start_follow *, struct _p_end *);

//
struct _start_follow * create_follow_list_case_2(struct _start * , struct _start *, struct _start_follow *);

//
struct _start_follow * add_follow_set(struct _start *, struct _p_end *, struct _start_follow *);

//
struct _start_follow * create_follow_list_case_3(struct _start *, struct _start *, struct _start_follow *);

//
struct _start_follow * follow_case3(struct _start *, struct _start *,  struct _start_follow * , struct _p_end *);

//
struct _table_head * create_parser_table( struct _start *, struct _start_follow *, struct _p_end *);

//
int display_table(struct _table_head * );

//
struct _table_head * finding_first_list(struct _start *, struct _start *, struct _start_follow *, struct _table_head *);

//
struct _table_head * add_entry_to_table(struct _start *,struct _start *, struct _p_end *, struct _p_end *, struct _table_head *, struct _start_follow *);

//
struct _table_head * calculate_first_list( struct _start *,struct  _start *, struct _p_end *, struct _start_follow *, struct _table_head * );

//
struct _table_head * add_entry_to_table_with_follow(struct _start *, struct _p_end *, struct _p_end *, struct _table_head*); 

//
int generate_input_file(struct _start *, struct _start_follow *, struct _p_end * l, struct _table_head *);

//for removing he left recursion from the scanned grammer
struct _start * left_recursion(struct _start * head);

//for finding the next production rule which is non recursive production rule
struct _start * find_next_nonrecursive( struct _start * , struct _start *, struct _p_start *);

//for removing the recursive grammer from the data structure 
struct _start * remove_recursive_grammer(struct _start*, struct _start*, struct _p_start*, struct _p_start*, struct _p_end*);

/*for adding the extra non terminal production rule to the data structure			*/
struct _start * add_another_non_terminal(struct _start*, struct _p_end*, char *);

//for removing the repetative symbols in the first follow list
struct _start_follow * remove_repetative_symbols(struct _start_follow *);

//
struct _p_end * remove_symbols(struct _p_end * );

//
struct _p_end * delete_node(struct _p_end *, struct _p_end *);

//
int first_follow_display1(struct _start_follow * head_follow);

//
int travers1(struct _p_end *);

//
int process_input_parser_table(struct _start *,struct _start_follow *, struct _p_end * ,  struct _table_head * );

//
struct _p_end * make_list_of_input_string(struct _p_end * );

//
struct _p_end * make_list_of_stack_string(struct _p_end *, struct _start *);

//
struct _p_end * change_stack_symbol(struct _p_end*, struct _p_end*, struct _p_end*, struct _p_end*, struct _table_head *);

//
int display_list(struct _p_end* );

//
struct _p_end * reverse_list(struct _p_end * );
