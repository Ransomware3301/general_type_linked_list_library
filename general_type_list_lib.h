/*
 *  Program:    General-Type Linked List Library
 *				(Function Declarations)
 *
 *  Made by:    Ransomware3301 (https://www.github.com/ransomware3301)
 *  Date:       15-11-2023
 */ 


/* ==== Type Definitions ==== */


#define FALSE 0
#define TRUE 1

typedef int BOOL;
typedef int TYPE;


typedef struct list {
	TYPE val;
	struct list *next;
} list_t;


/* ==== Function Declarations ==== */


/* Output */
void output_list(list_t*);

/* Sorting */
void insertion_sort(list_t*);

/* Actions */
list_t * push(list_t*, TYPE);
list_t * append(list_t*, TYPE);
list_t * delete(list_t*, TYPE);
list_t * delete_all_instances(list_t*, TYPE);
list_t * insert_in_order(list_t*, TYPE);
BOOL find(list_t*, TYPE);
BOOL find_Recursive(list_t*, TYPE);
list_t * remove_duplicates(list_t*);
list_t * free_list(list_t*);

/* Miscellaneous */
int list_length(list_t*);
int list_length_Recursive(list_t*);
