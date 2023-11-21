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
	#define FORMAT "%d"
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


/* ==== Function Definitions ==== */


/* 
 *  Outputs the list to terminal with the following formatting:
 *  -   (Example) With a list of 3 elements, the output 
 *      looks like this:
 *              
 *      (elem1.val) -> (elem2.val) -> (elem3.val)
 */
void output_list(list_t *head)
{
    list_t *ptr;


    if (head)
    {
        printf("\n");

        if(head->next != NULL)
        {
            for (ptr = head; ptr != NULL && ptr->next != NULL; ptr = ptr->next)
            {
                printf(str_concat(FORMAT, " -> "), ptr->val);
            }
            printf(str_concat(FORMAT, "\n\n"), ptr->val);
        }   
        else
        {
            printf(str_concat(FORMAT, "\n\n"), head->val);
        }
    }
    else
    {
        printf("\n[EMPTY LIST]\n");
    }
}


/* 
 *  Uses the Insertion Sort Algorithm to sort the passed list
 */
void insertion_sort(list_t *head)
{
    list_t *elem1, *elem2;
    TYPE temp;


    if (head)
    {
        for (elem1 = head; elem1 != NULL; elem1 = elem1->next)
        {
            for (elem2 = elem1->next; elem2 != NULL; elem2 = elem2->next)
            {
                if (elem1->val > elem2->val)
                {
                    temp = elem1->val;
                    elem1->val = elem2->val;
                    elem2->val = temp;
                }
            }
        }
    }
}


/* 
 *  Pushes to the top of the list the new value passed as val
 */
list_t * push(list_t *head, TYPE val)
{
    list_t *temp;


    if (( temp = (list_t *)malloc(sizeof(list_t)) ))
    {
        temp->val = val;
        temp->next = head;
        head = temp;
    } 
    else
    {
        printf("[ push() ] Error: Memory allocation unsuccessful.\n");
    }

    return head;
}


/* 
 *   Appends to the end of the list the new value passed as val
 */
list_t * append(list_t *head, TYPE val)
{
    list_t *ptr, *temp;


    if (( temp = (list_t *)malloc(sizeof(list_t)) ))
    {
        if (head)
        {
            for (ptr = head; ptr->next != NULL; ptr = ptr->next)
                ;

            temp->next = NULL;
            temp->val = val;
            ptr->next = temp;
        }
        else
        {
            head = temp;
            head->next = NULL;
            head->val = val;
        }
    }
    else
    {
        printf("[ append() ] Error: Memory allocation unsuccessful.\n");
    }

    return head;
}


/* 
 *  Deletes the first instance of val found in the list
 */
list_t * delete(list_t *head, TYPE val)
{
    list_t *prev, *ptr;
    bool_t found;


    if (head)
    {
        if (head->val == val)
        {
            ptr = head;
            head = head->next;
            free(ptr);
        }
        else
        {
            prev = head;
            ptr = head->next;
            found = false;

            while (ptr != NULL && !found)
            {
                if (ptr->val == val)
                {
                    found = true;
                }
                else
                {
                    prev = ptr;
                    ptr = ptr->next;
                }
            }

            if (found == true)
            {
                prev->next = ptr->next;
                free(ptr);
            }
        }
    }

    return head;
}


/* 
 *  Deletes all instances of val found in the list
 */
list_t * delete_all_instances(list_t *head, TYPE val)
{
    list_t *ptr, *prev, *del;


    if (head)
    {
        while (head != NULL && head->val == val)
        {
            del = head;
            head = head->next;
            free(del);
        }
    }
    
    if (head)
    {    
        prev = head;
        ptr = head->next;
        
        while (ptr != NULL)
        {
            if (ptr->val == val)
            {
                del = ptr; 
                ptr = ptr->next;
                prev->next = ptr;
                free(del);
            }
            else
            {
                prev = ptr;
                ptr = ptr->next;
            }
        }
    }

    return head;
}


/* 
 *  Inserts val into the list in the position where the next element is greater than val 
 */
list_t * insert_in_order(list_t *head, TYPE val)
{   
    list_t *ptr, *temp, *prev;


    if (( temp = (list_t *)malloc(sizeof(list_t)) ))
    {
        if (head)
        {
            if (val < head->val)
            {
                temp->val = val;
                temp->next = head;
                head = temp;
            }
            else
            {
                prev = head;
                ptr = head->next;

                while (ptr && ptr->val < val)
                {
                    prev = ptr;
                    ptr = ptr->next;
                }   

                temp->val = val;
                temp->next = ptr;
                prev->next = temp;
            }
        }
        else
        {
            head = temp;
            head->val = val;
            head->next = NULL;
        }
    }
    else
    {
        printf("[ append() ] Error: Memory allocation unsuccessful.\n");
    }
    
    return head;
}


/* 
 *  Returns 1 (TRUE) if val was found in the list, 0 (FALSE) otherwise
 */
bool_t find(list_t *head, TYPE val)
{
    list_t *ptr;
    bool_t found;

    found = false;

    if (head)
    {
        ptr = head;

        while (ptr != NULL && !found)
        {
            if (ptr->val == val)
            {
                found = true;
            }
            else
            {
                ptr = ptr->next;
            }
        }
    }

    return found;
}


/* 
 *  Returns 1 (TRUE) if val was found in the list, 0 (FALSE) otherwise, but in a Recursive fashion
 */
bool_t find_Recursive(list_t *head, TYPE val)
{
    if (head)
    {
        if (head->val == val)
        {
            return true;
        }
        else
        {
            return find_Recursive(head->next, val);
        }
    }

    return false;
}


/* 
 *  Removes every duplicate value in the list
 */
list_t * remove_duplicates(list_t *head)
{
    list_t *prev, *ptr1, *ptr2;
    TYPE actual;

    if (head)
    {
        ptr1 = head;

        while (ptr1 != NULL)
        {
            actual = ptr1->val;
            prev = ptr1;
            ptr2 = ptr1->next;

            while (ptr2 != NULL)
            {
                if (ptr2->val == actual)
                {
                    prev->next = ptr2->next;
                    free(ptr2);
                    ptr2 = prev->next;
                }
                else
                {
                    prev = ptr2;
                    ptr2 = ptr2->next;
                }
            }

            ptr1 = ptr1->next;
        }   
    }

    return head;
}


/* 
 *  Deletes from memory all the elements of the passed list
 */
list_t * free_list(list_t *head)
{
    list_t *del;
    
    if (head)
    {
        while (head != NULL)
        {
            del = head;
            head = head->next;
            free(del);
        }
    }

    return head;
}


/*
 *  Given a string of values separated with "sep", returns a list of strings
 */
list_t * string_to_list(char *str, char *sep)
{
    list_t *head;
    char *temp_str;
    int temp_str_dim, sep_len, str_len;
    int r, l, i;
    bool_t end;


    head = NULL;

    if ( str && sep )
    {
        r = 0;
        l = 0;
        str_len = strlen(str);
        sep_len = strlen(sep);
        end = false;

        while ( r < str_len && *(str + r) != '\0' )
        {
            end = (*(str + r + 1) == '\0');

            if ( !end )
            {
                i = 0;

                while ( (r + i) < str_len &&  i < sep_len && *(str + r + i) == *(sep + i) )
                {
                    i++;
                }
            }

            if (i == sep_len || end == true)
            {
                temp_str_dim = r - l + (end ? 1 : 0);

                if (( temp_str = (char *)malloc(sizeof(char) * (temp_str_dim + 1)) ))
                {
                    for (i = 0; i < temp_str_dim; i++)
                    {
                        *(temp_str + i) = *(str + l + i);
                    }

                    /* String terminator at the end of s */
                    *(temp_str + i) = '\0';
                    
                    head = append(head, convert(temp_str));
                }
                else
                {
                    printf("[ string_to_list() ] Error: Memory allocation unsuccessful (temp_str)\n");
                }

                r += sep_len;
                l = r;
            }
            else
            {
                r++;
            }
        }
    }

    return head;
}


/* 
 *  Returns the number of elements in the list
 */
int list_length(list_t *head)
{
    list_t *ptr;
    int dim;


    dim = 0;

    if (head)
    {
        ptr = head;
        
        while (ptr != NULL)
        {
            dim++;
            ptr = ptr->next;
        }
    }

    return dim;
}


/* 
 *  Returns the number of elements in the list, but in a Recursive fashion
 */
int list_length_Recursive(list_t *head)
{
    if (head)
    {
        return 1 + list_length_Recursive(head->next);
    }
    else 
    {
        return 0;
    }
}


/*
 *  Concatenates two strings
 */
char * str_concat(char *str1, char *str2)
{
    int len1, len2;
    int i;
    char *s;


    len1 = strlen(str1);
    len2 = strlen(str2);

    if (( s = (char *)malloc(sizeof(char) * (len1 + len2 + 1)) ))
    {
        for (i = 0; i < len1; i++)
        {
            *(s + i) = *(str1 + i);
        }

        for (i = 0; i < len2; i++)
        {
            *(s + len1 + i) = *(str2 + i);
        }

        /* String terminator at the end of s */
        *(s + len1 + len2) = '\0';
    }
    else
    {
        printf("[ str_concat() ] Error: Memory allocation unsuccesful\n");
    }

    return s;
}


/*
 *  Converts the passed string into the selected variable type
 */
TYPE convert(char *str)
{
    TYPE res;
    int left_digits, right_digits;
    int i, j, val;


    res = -1;


    if (IS_SHORT_INT || IS_INT || IS_LONG_INT)
    {   
        if (str)
        {
            res = 0;

            for (left_digits = 0; *(str + left_digits) != '\0'; left_digits++)
                ;

            i = left_digits - 1;

            while (i >= 0)
            {
                val = *(str + left_digits - i - 1) - ZERO_CHAR;
                res += val * pow(10, i);
                i--;
            }
        }
    }
    else if (IS_FLOAT || IS_DOUBLE || IS_LONG_DOUBLE)
    {
        if (str)
        {
            res = 0;

            for (left_digits = 0; *(str + left_digits) != '.'; left_digits++)
                ;

            i = left_digits - 1;
            
            while (i >= 0)
            {
                val = *(str + left_digits - i - 1) - ZERO_CHAR;
                res += val * pow(10, i);
                i--;
            }

            for (right_digits = 0; *(str + left_digits + right_digits) != '\0'; right_digits++)
                ;

            j = 1;
            right_digits--;

            while (j <= right_digits)
            {
                val = *(str + left_digits + j) - ZERO_CHAR;
                res += val * pow(10, (-j) );
                j++;
            }
        }
    }

    return res;
}
