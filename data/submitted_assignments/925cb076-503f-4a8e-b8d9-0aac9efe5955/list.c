#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "list.h"

#ifdef UNIT_TESTING
/* Redirect printf to a function in the test application so it's possible to
 * test the standard output. You can ignore this; it's not relevant to the
 * assignment. */
#ifdef printf
#undef printf
#endif /* printf */
extern int test_printf(const char *format, ...);
#define printf test_printf
#endif

#define MAX_ITEM_PRINT_LEN 100

// Note: All list_ functions should return a status code
// EXIT_FAILURE or EXIT_SUCCESS to indicate whether the operation was
// successful or not.

// create a new list
int list_init(node **head)
{
    int status = EXIT_SUCCESS;

    if (head == NULL)
    {
        status = EXIT_FAILURE;
    }
    else
    {
        *head = NULL;
    }
    return status;
}


// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {

    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int status = EXIT_SUCCESS;
    if (head == NULL)
    {
        status = EXIT_FAILURE;
    }
    else
    {
        if (head->next == NULL)
        {
            sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
        }
        else
        {
            sprintf(str, "%d * %s @ $%.2f ea, %s", head->quantity, head->item_name, head->price, list_item_to_string(head->next, str));
        }
    }
    return status;
}




// print the list to stdout
// This should be in the format of:
// "pos: quantity * item_name @ $price ea", where
//   pos is the position of the item in the list,
//   item_name is the item_name of the item and
//   price is the float price of the item formatted with 2 decimal places.
// For example:
// """1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// 3: 4 * apple @ $3.00 ea
// """
// It should return a newline character at the end of each item.
// It should not have a leading newline character.
int list_print(node *head) {
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int pos = 0;
    char str[MAX_ITEM_PRINT_LEN];
    while (head != NULL)
    {
        pos++;
        if (list_item_to_string(head, str) == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
        printf("%d: %s\n", pos, str);
        head = head->next;
    }
    return EXIT_SUCCESS;
}



// add a new item (name, price, quantity) to the list at position pos,
//   such that the added item is the item at position pos
// For example:
// If the list is:
// 1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// and you call list_add_item_at_pos(&head, "apple", 3.0, 4, 2)
// the list should be:
// 1: 3 * banana @ $1.00 ea
// 2: 4 * apple @ $3.00 ea
// 3: 2 * orange @ $2.00 ea
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int status = EXIT_SUCCESS;
    node *new_node = NULL;
    if (head == NULL || item_name == NULL || quantity < 0 || pos < 0)
    {
        status = EXIT_FAILURE;
    }
    else
    {
        new_node = (node*)malloc(sizeof(node));
        strcpy(new_node->item_name, item_name);
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = NULL;
        if (*head == NULL)
        {
            *head = new_node;
            return status;
        }
        else if (pos == 0)
        {
            new_node->next = *head;
            *head = new_node;
        }
        else
        {
            status = list_add_item_at_pos(&((*head)->next), item_name, price, quantity, pos - 1);
            if (status == EXIT_FAILURE)
            {
                free(new_node);
                return status;
            }
            if ((*head)->next == NULL)
            {
                (*head)->next = new_node;
            }
        }
    }
    return status;
}







// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    while (pos--) {
        head = &(*head)->next;
    }

    node* temp = *head;
    temp->item_name = item_name;
    temp->price = price;
    temp->quantity = quantity;

    return EXIT_SUCCESS;
}


// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    while (pos--) {
        head = &(*head)->next;
    }

    node* temp = *head;
    *head = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}



// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    while (pos1--) {
        head = &(*head)->next;
    }

    node* temp = *head;
    *head = temp->next;

    while (pos2--) {
        head = &(*head)->next;
    }

    node* temp2 = *head;
    *head = temp2->next;

    if (temp2->next == NULL) {
        temp2->next = temp;
    }
    else {
        temp2->next = temp->next;
    }

    temp->next = temp2;
    return EXIT_SUCCESS;
}



// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* curr = head;
    node* max = head;
    int position = 0;

    while (curr != NULL) {
        if (curr->price > max->price) {
            max = curr;
            position = 1;
        }
        curr = curr->next;
        position++;
    }

    *pos = position;

    return EXIT_SUCCESS;
}




// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* curr = head;
    float cost = 0;

    while (curr != NULL) {
        cost += curr->price * curr->quantity;
        curr = curr->next;
    }

    *total = cost;

    return EXIT_SUCCESS;
}


// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open the file");
        return EXIT_FAILURE;
    }

    node* curr = head;
    while (curr != NULL) {
        fprintf(file, "%s,%f,%d\n", curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }

    fclose(file);

    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head)
{

    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *ptr1, *ptr2, *dup;
    ptr1 = head;

    /* Pick elements one by one */
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;

        while (ptr2->next != NULL) {
            if (ptr1->data == ptr2->next->data) {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete (dup);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }

    return EXIT_SUCCESS;
}

