/*
 *  Program:    General-Type Linked List Library
 *              (Function Definitions)
 *              
 *  Made by:    Ransomware3301 (https://www.github.com/ransomware3301)
 *  Date:       15-11-2023
 */ 


#include "general_type_list_lib.h"


/* ==== Function Definitions ==== */


/* 
 *  Outputs the list to terminal with the following formatting:
 *  -   (Example) With a list of 3 elements, the output 
 *      looks like this:
 *              
 *      (elem1.val) -> (elem2.val) -> (elem3.val)
 * 
 *  NOTE: 
 *  -   The commented printf() functions are the ones that only allow integers to be displayed, they
 *      are instead replaced with the general-type printf(), which uses the custom str_concat() function
 *      to correctly replace the format parameter in the output string, so that it corresponds to the 
 *      correct format parameter type.
 * 
 *  -   (Example) 
 *      -   If type selected is int  -> %d is used in printf() output format string
 *      -   If type selected is char -> %c is used in printf() output format string
 *      -   etc...
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
                /* printf("%d -> ", ptr->val); */
                printf(str_concat(FORMAT, " -> "), ptr->val);
            }
            printf(str_concat(FORMAT, "\n\n"), ptr->val);
            /* printf("%d\n\n", ptr->val); */
        }   
        else
        {
            printf(str_concat(FORMAT, "\n\n"), head->val);
            /* printf("%d\n\n", head->val); */
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
    int temp_str_dim, sep_len;
    int r, l, i;


    head = NULL;

    if ( str && sep )
    {
        /* 
         *  Example of left-right sizing:
         *      l       r
         *      |       |
         *      H e l l o \0
         * 
         *      str_len = r - l + 1;
         */

        r = 0;
        l = 0;
        sep_len = strlen(sep);

        while ( *(str + r) != '\0' )
        {
            i = 0;

            if ( *(str + r + i) == *(sep + i) )
            {
                do
                {
                    i++;
                } while (*(str + r + i) == *(sep + i) && i < sep_len);

                if (i == sep_len)
                {
                    temp_str_dim = r - l + 1;

                    if (( temp_str = (char *)malloc(sizeof(char) * temp_str_dim) ))
                    {
                        for (i = 0; i < temp_str_dim; i++)
                        {
                            *(temp_str + i) = *(str + l + i);
                        }
                        
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
    if (str)
    {
        if (IS_CHAR)
        {
            return *(str);
        }          
        else if (IS_SHORT_INT)
        {
            return ascii_to_short_int(str);
        }      
        else if (IS_INT)
        {
            return ascii_to_int(str);
        }          
        else if (IS_LONG_INT)
        {
            return ascii_to_long_int(str);
        }      
        else if (IS_FLOAT)
        {
            return ascii_to_float(str);
        }        
        else if (IS_DOUBLE)
        {
            return ascii_to_double(str);
        }
        else if (IS_LONG_DOUBLE)
        {
            return ascii_to_long_double(str);
        }
    }

    return (TYPE) 0;
}


/*
 *  Converts the passed string into its short int value
 */
short int ascii_to_short_int(char *str)
{
    short int res;
    int digits, i;
    int val;


    res = -1;
    
    if (str)
    {
        for (digits = 0; *(str + digits) != '\0'; digits++)
            ;

        i = digits - 1;

        while (i >= 0)
        {
            val = *(str + digits - i - 1) - ZERO_CHAR;
            if (val >= 0 && val <= 9)
            {
                res += val * pow(10, i);
                i--;
            }
        }
    }

    return res;
}


/*
 *  Converts the passed string into its int value
 */
int ascii_to_int(char *str)
{
    int res;
    int digits, i;
    int val;


    res = -1;
    
    if (str)
    {
        for (digits = 0; *(str + digits) != '\0'; digits++)
            ;

        i = digits - 1;

        while (i >= 0)
        {
            val = *(str + digits - i - 1) - ZERO_CHAR;
            res += val * pow(10, i);
            i--;
        }
    }

    return res;
}


/*
 *  Converts the passed string into its int value
 */
long int ascii_to_long_int(char *str)
{
    long int res;
    int digits, i;
    int val;


    res = -1;
    
    if (str)
    {
        for (digits = 0; *(str + digits) != '\0'; digits++)
            ;

        i = digits - 1;

        while (i >= 0)
        {
            val = *(str + digits - i - 1) - ZERO_CHAR;
            res += val * pow(10, i);
            i--;
        }
    }

    return res;
}


/*
 *  Converts the passed string into its float value
 */
float ascii_to_float(char *str)
{
    float res;
    int left_digits, right_digits;
    int i, j, val;


    res = -1;

    if (str)
    {
        /* 
         * Adding the number that is LEFT of the decimal point
         */
        for (left_digits = 0; *(str + left_digits) != '.'; left_digits++)
            ;

        i = left_digits - 1;
        
        while (i >= 0)
        {
            val = *(str + left_digits - i - 1) - ZERO_CHAR;
            res += val * pow(10, i);
            i--;
        }

        /* 
         * Adding the number that is RIGHT of the decimal point
         */
        for (right_digits = 0; *(str + left_digits + right_digits) != '\0'; right_digits++)
            ;

        j = 1;

        while (j <= right_digits)
        {
            val = *(str + left_digits + j) - ZERO_CHAR;
            res += val * pow(10, (-j) );
            j++;
        }
    }

    return res;
}


/*
 *  Converts the passed string into its double value
 */
double ascii_to_double(char *str)
{
    double res;
    int left_digits, right_digits;
    int i, j, val;


    res = -1;

    if (str)
    {
        /* 
         * Adding the number that is LEFT of the decimal point
         */
        for (left_digits = 0; *(str + left_digits) != '.'; left_digits++)
            ;

        i = left_digits - 1;
        
        while (i >= 0)
        {
            val = *(str + left_digits - i - 1) - ZERO_CHAR;
            res += val * pow(10, i);
            i--;
        }

        /* 
         * Adding the number that is RIGHT of the decimal point
         */
        for (right_digits = 0; *(str + left_digits + right_digits) != '\0'; right_digits++)
            ;

        j = 1;

        while (j <= right_digits)
        {
            val = *(str + left_digits + j) - ZERO_CHAR;
            res += val * pow(10, (-j) );
            j++;
        }
    }

    return res;
}


/*
 *  Converts the passed string into its long double value
 */
long double ascii_to_long_double(char *str)
{
    long double res;
    int left_digits, right_digits;
    int i, j, val;


    res = -1;

    if (str)
    {
        /* 
         * Adding the number that is LEFT of the decimal point
         */
        for (left_digits = 0; *(str + left_digits) != '.'; left_digits++)
            ;

        i = left_digits - 1;
        
        while (i >= 0)
        {
            val = *(str + left_digits - i - 1) - ZERO_CHAR;
            res += val * pow(10, i);
            i--;
        }

        /* 
         * Adding the number that is RIGHT of the decimal point
         */
        for (right_digits = 0; *(str + left_digits + right_digits) != '\0'; right_digits++)
            ;

        j = 1;

        while (j <= right_digits)
        {
            val = *(str + left_digits + j) - ZERO_CHAR;
            res += val * pow(10, (-j) );
            j++;
        }
    }

    return res;
}
