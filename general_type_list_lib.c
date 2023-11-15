/*
 *  Program:    General-Type Linked List Library
 *              (Function Definitions)
 *              
 *  Made by:    Ransomware3301 (https://www.github.com/ransomware3301)
 *  Date:       15-11-2023
 */ 


#include <stdio.h> 
#include <stdlib.h>
#include "general_type_list_lib.h"


/* ==== Function Definitions ==== */


/* 
 *  Outputs the list to terminal with the following formatting:
 *      List of 3 elements:     (elem1.val) -> (elem2.val) -> (elem3.val)
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
                printf("%d -> ", ptr->val); 
            }
            printf("%d\n\n", ptr->val);
        }   
        else
        {
            printf("%d\n\n", head->val);
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
    BOOL found;


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
            found = FALSE;

            while (ptr != NULL && !found)
            {
                if (ptr->val == val)
                {
                    found = TRUE;
                }
                else
                {
                    prev = ptr;
                    ptr = ptr->next;
                }
            }

            if (found == TRUE)
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
BOOL find(list_t *head, TYPE val)
{
    list_t *ptr;
    BOOL found;

    found = FALSE;

    if (head)
    {
        ptr = head;

        while (ptr != NULL && !found)
        {
            if (ptr->val == val)
            {
                found = TRUE;
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
BOOL find_Recursive(list_t *head, TYPE val)
{
    if (head)
    {
        if (head->val == val)
        {
            return TRUE;
        }
        else
        {
            return find_Recursive(head->next, val);
        }
    }

    return FALSE;
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
