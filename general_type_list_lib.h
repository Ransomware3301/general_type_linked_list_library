/*
 *  Program:    General-Type Linked List Library
 *				(Function Declarations)
 *
 *  Made by:    Ransomware3301 (https://www.github.com/ransomware3301)
 *  Date:       15-11-2023
 */ 


#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define ZERO_CHAR '0'


/* ==== Type Selector and printf() Format Type Selector ==== */

/*
 *	TYPE CHANGER:
 *	- 	To change the type, just put the corresponding
 *		define directive to 1 and the others to 0 
 */

/* CHAR: Problem with scanf with the str terminator char '\0' - It gets read instead of an actual input */
#define IS_CHAR 0
#define IS_SHORT_INT 0
#define IS_INT 1
#define IS_LONG_INT 0
#define IS_FLOAT 0
#define IS_DOUBLE 0
#define IS_LONG_DOUBLE 0


#if IS_CHAR
	/* 
	 *	The space before %c is needed to avoid the scanf() to 
	 *	read a \n when present, which is problematic
	 */
	#define FORMAT " %c"
	typedef char TYPE;

#elif IS_SHORT_INT
    #define FORMAT "%hd"
	typedef short int TYPE;

#elif IS_INT
	#define FORMAT "%d"
	typedef int TYPE;

#elif IS_LONG_INT	
	#define FORMAT "%ld"
	typedef long int TYPE;

#elif IS_FLOAT
    #define FORMAT "%f"
	typedef float TYPE;

#elif IS_DOUBLE
    #define FORMAT "%f"
	typedef double TYPE;

#elif IS_LONG_DOUBLE
    #define FORMAT "%lf"
	typedef long double TYPE;

#else
	#error "ERROR: Variable and type aren't selected."
	/* 
	 *	These aren't compiled, due to the error being thrown up here, they are
	 * 	just needed to remove compiler errors and as a fallback default option
	 */
	char FORMAT[] = "%d";
	typedef int TYPE;
#endif


/* ==== Type Definitions ==== */


typedef enum bool 
{
	false,
	true
} bool_t;

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
bool_t find(list_t*, TYPE);
bool_t find_Recursive(list_t*, TYPE);
list_t * remove_duplicates(list_t*);
list_t * free_list(list_t*);
list_t * string_to_list(char*, char*);


/* Miscellaneous */
int list_length(list_t*);
int list_length_Recursive(list_t*);
char * str_concat(char*, char*);
TYPE convert(char *);
short int ascii_to_short_int(char *);
int ascii_to_int(char *);
long int ascii_to_long_int(char *);
float ascii_to_float(char *);
double ascii_to_double(char *);
long double ascii_to_long_double(char *);
