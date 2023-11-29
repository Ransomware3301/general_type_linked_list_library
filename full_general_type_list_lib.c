/*
 *  Program:    General-Type Linked List Library
 *
 *  Made by:    Ransomware3301 (https://www.github.com/ransomware3301)
 *  Date:       28-11-2023
 */


/*
 *  ====== HOW TO USE THIS LIBRARY ======
 *
 *  -   Copy this file in your workspace, then #include it in your program 
 *      and lastly put at the top of your program the following define directives:
 *  
 *          #define TYPE [your type of choice goes here]
 *          #define FORMAT [the printf and scanf format related to the chosen type]
 * 
 *      NOTE: it's MANDATORY that these two define directives up here are put BEFORE including
 *            the C library file named "full_general_type_list_lib.c" 
 * 
 *  -   Example:
 *      
 *          #define TYPE int
 *          #define FORMAT "%d"
 * 
 *      The compiler will automatically replace every TYPE word it finds in the code, thus
 *      adapting the functions/variables that have it to the chosen type.
 *      
 *      In regards to FORMAT, every "printf" and/or "scanf" function will be adapted 
 *      automatically to the correct format.
 *      In this case:
 *          
 *          printf("Hello World "FORMAT"\n", 10);    ==> This will print to terminal "Hello World 10" (and a newline), thus
 *                                                       the print format "%d" is correct in regards to the chosen "int" type.
 *          
 *          TYPE temp;
 *          scanf("Insert value: "FORMAT, &temp);    ==> This will be translated to the following string "Insert value: %d" 
 *                                                       and thus the input format "%d" is correct in regards to the chosen "int" type.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define ZERO_CHAR '0'


/*
 *	Initial check by compiler to see wether the TYPE and FORMAT were defined
 *	in the main C file
 */
#ifdef TYPE
	#ifdef FORMAT


/* ==== Type Definitions ==== */


typedef enum bool 
{
	false,
	true
} bool_t;


typedef struct list 
{
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
list_t * list_concat(list_t*, list_t*);
list_t * string_to_list(char*, char*);


/* Miscellaneous */
int list_length(list_t*);
int list_length_Recursive(list_t*);
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
                printf(FORMAT" -> ", ptr->val);
            }
            printf(FORMAT"\n\n", ptr->val);
        }   
        else
        {
            printf(FORMAT"\n\n", head->val);
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
 *  Joins the two passed lists into a single one
 */
list_t * list_concat(list_t *l1, list_t *l2)
{
    list_t *res, *ptr;


    res = NULL;
    ptr = l1;

    while (ptr)
    {
        res = append(res, ptr->val);
        ptr = ptr->next;
    }

    ptr = l2;

    while (ptr)
    {
        res = append(res, ptr->val);
        ptr = ptr->next;
    }

    return res;
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

    if (str && sep)
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
 *  Converts the passed string into the selected variable type
 */
TYPE convert(char *str)
{
    TYPE res;
    int val;
    int left_digits, right_digits;
    int digits, i, j;
    bool_t is_negative;
    

    res = 0;
    is_negative = false;

    if (str)
    {
        if (strcmp(FORMAT, " %c"))
        {  
            if (*(str) == '-')
            {
                is_negative = true;
            }

            left_digits = 0;
            digits = strlen(str) - 1;

            while ((str + left_digits) && *(str + left_digits) != '.' && *(str + left_digits) != '\0')
            {
                left_digits++;
            }

            i = left_digits - 1;
            
            if (is_negative)
            {
                /* 
                *  If its a negative number, then the str to consider is all shifted 
                *  right by 1 position due to the minus sign in front, hence the different 
                *  indexes in the formulas 
                */
                while (i > 0)
                {
                    val = *(str + left_digits - i) - ZERO_CHAR;
                    res += val * pow(10, i - 1);
                    i--;
                }   
            }
            else
            {   
                while (i >= 0)
                {
                    val = *(str + left_digits - i - 1) - ZERO_CHAR;
                    res += val * pow(10, i);
                    i--;
                }
            }

            /* 
            *  If condition means "if there's a decimal point in str, then
            *  it's a float, else it's an integer"
            */
            if (left_digits < strlen(str))
            {
                /* Case where str contains a floating point value */
                right_digits = digits - left_digits;
                j = 1;

                while (j <= right_digits)
                {
                    val = *(str + left_digits + j) - ZERO_CHAR;
                    res += val * pow(10, (-j) );
                    j++;
                }
            }

            if (is_negative)
            {
                res = -res;
            }
        }
        else
        {
            /* If it's a char, then the only logical thing to do is to return it directly */
            res = *(str);
        }
    }

    return res;
}


	#endif
#endif  
