#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

#include "reflist.h"

// Main API functions

int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // see the following for the format you need to implement:

    // was fighting the language model whenever I was trying
    // to do anything and I ended up giving up, because whenever
    // I would start with an idea, it would suggest something that 
    // looked good at first sight, I would add it to my own code
    // and then I would spend time debugging some of its code rather
    // than develop my ideas

    // for the other functions where it gave me the answer straight
    // up and it just worked, I felt like I just cheated and got
    // someone else to do the work for me

    // I ended up not having too much time to finish and the couple
    // hours I spent on this was mostly just fighting with the robot
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: id-175, omitted, human, missing return
    else {}
}

int list_print(node *head) {
    // TODO: Implement this function, 
    node * ptr = head;
    int pos = 1;
    char * str = malloc(MAX_ITEM_PRINT_LEN);
    // bug 2: id-314, omitted, human, missing check for head == NULL
    while(ptr->next != NULL){
        // bug 3: id-311, omitted, approx-0.23, doesn't check return value of list_item_to_string
        list_item_to_string(ptr, str);
        // bug 4: id-313, omitted, approx-0.23, maybe uninit str
        printf("%d: %s\n", pos, str);
        ptr = ptr->next;
        pos++;
    }
    // bug 1: id-312, omitted, human, memory leak, failing to free str
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-33, omitted, codex, missing check for head == NULL
    // It did it all by itself, I didn't even have to do anything for this part
    // cool I guess...
    // TODO: Implement this 
    node * new_node = malloc(sizeof(node));
    // bug 2: id-32, present, codex, id-missing strdup
    new_node->item_name = item_name; 
    new_node->price = price;
    new_node->quantity = quantity;
    if (*head == NULL) {
        new_node->next = NULL;
    } else {
        node * ptr = *head;
        for (int i = 0; i < pos - 2; i++) {
            if (ptr->next == NULL) {
                // bug 3: id-31, omitted, human, memory leak on EXIT_FAILURE
                return EXIT_FAILURE; 
            }
            ptr = ptr->next;
        }
        new_node->next = ptr->next;
        ptr->next = new_node;
    }
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}


