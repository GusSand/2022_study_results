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
    *head = NULL;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // cannot print NULL node
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    // store formatted string in str
    int len = sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    if (len < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
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
    node* ptr = head;
    char str[100];
    int counter = 1;
    
    // loop until end of list and print each item
    while (ptr != NULL) {
        int status = list_item_to_string(ptr, str);
        if (status == EXIT_FAILURE) { // check for error
            return EXIT_FAILURE;
        }

        printf("%d: %s\n", counter, str);
        ptr = ptr->next;
        counter++;
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // pos must be an integer >= 1
    if (pos < 1) {
        return EXIT_FAILURE;
    }

    node* prev_ptr = NULL;
    node* next_ptr = *head; // node that will be pushed down 1 index (curr node at pos)

    int counter = 1;
    while(counter < pos && next_ptr != NULL) {
        prev_ptr = next_ptr;
        next_ptr = next_ptr->next;
        counter++;
    }

    // counter should be equal to pos by end of while loop
    // otherwise this means we've looped until end of list and 
    // pos exceeds list length
    if (counter != pos) {
        return EXIT_FAILURE;
    }
    

    // make new node
    node* new_item_ptr = malloc(sizeof(node));
    new_item_ptr->item_name = malloc(strlen(item_name) + 1);
    strcpy(new_item_ptr->item_name, item_name);
    new_item_ptr->price = price;
    new_item_ptr->quantity = quantity;
    new_item_ptr->next = next_ptr;

    // case: pos is not 1, hence prev_str != NULL
    if (pos != 1) {
        prev_ptr->next = new_item_ptr;
    } else {
        *head = new_item_ptr; // update head ptr if pos == 1
    }

    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // pos must be an integer >= 1
    if (pos < 1) {
        return EXIT_FAILURE;
    }

    int counter = 1;
    node* ptr = *head;

    // loop until ptr points to item or ptr reaches end of list
    while(ptr != NULL && counter < pos) {
        ptr = ptr->next;
        counter++;
    }

    // end of list, ptr is NULL, cannot modify non-existing item
    if (ptr == NULL) {
        return EXIT_FAILURE;
    }

    // update existing item
    free(ptr->item_name);
    ptr->item_name = malloc(strlen(item_name) + 1);
    strcpy(ptr->item_name, item_name);
    ptr->price = price;
    ptr->quantity = quantity;

    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // pos must be an integer >= 1
    if (pos < 1) {
        return EXIT_FAILURE;
    }

    node* prev_ptr = NULL;  // node before node to be removed
    node* rem_ptr = *head; // node that will be removed (curr node at pos)

    int counter = 1;
    // loop until rem_ptr points to the node to be removed or reaches end of list
    while(counter < pos && rem_ptr != NULL) {
        prev_ptr = rem_ptr;
        rem_ptr = rem_ptr->next;
        counter++;
    }

    // cannot remove end of list/NULL
    if (rem_ptr == NULL) {
        return EXIT_FAILURE;
    }


    // case: pos is not 1, hence prev_str != NULL
    if (pos != 1) {
        prev_ptr->next = rem_ptr->next;
    } else {
        *head = rem_ptr->next; // note that rem_ptr = *head in this case
    }

    // free memory
    free(rem_ptr->item_name);
    free(rem_ptr);

    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // positions must be an integer >= 1
    if (pos1 < 1 || pos2 < 1) {
        return EXIT_FAILURE;
    }

    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }

    node* ptr1 = *head;
    node* ptr2 = *head;
    int counter = 1;

    // loop until both ptrs are set or reach end of list
    while(ptr1 != NULL && ptr2 != NULL && (counter < pos1 || counter < pos2)) {
        if (counter < pos1) {
            ptr1 = ptr1->next;
        }
        if (counter < pos2) {
            ptr2 = ptr2->next;
        }

        counter++;
    }

    // cannot swap with end of list (NULL)
    if (ptr1 == NULL || ptr2 == NULL) {
        return EXIT_FAILURE;
    }

    // swap attr
    char* temp_name = ptr1->item_name;
    float temp_price = ptr1->price;
    int temp_quantity = ptr1->quantity;

    ptr1->item_name = ptr2->item_name;
    ptr1->price = ptr2->price;
    ptr1->quantity = ptr2->quantity;

    ptr2->item_name = temp_name;
    ptr2->price = temp_price;
    ptr2->quantity = temp_quantity;


    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // set pos of node item with highest price to 0 if list empty
    if (head == NULL) {
        *pos = 0;
        return EXIT_SUCCESS;
    }


    node* ptr = head;
    int highest_price = 0;
    int counter = 1;
    
    // loop through list
    while(ptr != NULL) {
        // new high price found
        if (ptr->price > highest_price) {
            highest_price = ptr->price;
            *pos = counter;
        }

        ptr = ptr->next;
        counter++;
    }

    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    node* ptr = head;
    float total_cost = 0;

    // loop through list and sum total cost
    while(ptr != NULL) {
        total_cost += (ptr->price * ptr->quantity);
        ptr = ptr->next;
    }

    // set total cost
    *total = total_cost;

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

    // open file and check for error
    FILE* fileptr = fopen(filename, "w");
    if (fileptr == NULL) {
        return EXIT_FAILURE;
    }

    node* ptr = head;
    char str[100];

    // loop through list and write each item in specified format
    while(ptr != NULL) {
        fprintf(fileptr, "%s,%.2f,%d\n", ptr->item_name, ptr->price, ptr->quantity);
        ptr = ptr->next;
    }

    // close file
    fclose(fileptr);

    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // open file and check for error
    FILE* fileptr = fopen(filename, "r");
    if (fileptr == NULL) {
        return EXIT_FAILURE;
    }

    node* ptr = *head;
    int counter = 1;

    // loop through list and until it reaches end to set counter
    while(ptr != NULL) {
        counter++;
        ptr = ptr->next;
    }

    char name[100];
    float price;
    int quantity;

    // scan through file and set the attributes (note %*c to ignore , delimiter)
    while(fscanf(fileptr, "%[^,],%f%*c%d\n", name, &price, &quantity) != EOF) {
        // add item to end of list
        int status = list_add_item_at_pos(head, name, price, quantity, counter);
        if (status == EXIT_FAILURE) { // check item added correctly
            return EXIT_FAILURE;
        }

        counter++;
    }

    // close file
    fclose(fileptr);

    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    node* ptr = *head;
    int ptr_counter = 1;

    // loops through each item in list
    while (ptr != NULL) {
        node* dup_ptr = ptr->next; // checks for duplicates
        int dup_counter = ptr_counter + 1;

        // loops through rest of list starting with the node after ptr
        while(dup_ptr != NULL) {
            // update quantity if the two pointers have same item name
            if(strcmp(ptr->item_name, dup_ptr->item_name) == 0) {
                node* rem_ptr = dup_ptr;
                ptr->quantity += rem_ptr->quantity; // update quantity
                dup_ptr = dup_ptr->next; // move dup_ptr to next pointer

                // remove duplicate and check for error
                int status = list_remove_item_at_pos(head, dup_counter);
                if (status == EXIT_FAILURE) {
                    return EXIT_FAILURE;
                }
                continue;
            }

            dup_ptr = dup_ptr->next;
            dup_counter++;
        }

        ptr = ptr->next;
        ptr_counter++;
    }


    return EXIT_SUCCESS;
}

