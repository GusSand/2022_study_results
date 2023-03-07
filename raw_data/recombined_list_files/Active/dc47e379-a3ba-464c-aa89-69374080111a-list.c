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
    // bug 1: id-258, omitted, human, missing check for str == NULL
    // bug 2: id-259, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-260, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    // bug 4: id-257, omitted, human, missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);

    // char output[] = itoa(head->quantity) + " * " + head->item_name + " @ " + "$" + printf("%.2f", head->price) + " ea";
    // char output[100] = quantityStr + " * " + head->item_name;
    // char output[100] = strcat(quantityStr, " ");
    // str = strcat(quantityStr, " ");

    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = head;
    int pos = 1;
    while (curr != NULL) {
      char itemAsString[100];
      // bug 1: id-362, omitted, human, doesn't check return value of list_item_to_string
      list_item_to_string(curr, itemAsString);
      // bug 2: id-363, present, human, maybe uninit itemAsString
      printf("%d: %s\n", pos, itemAsString);
      curr = curr->next;
      pos += 1;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-113, omitted, human, missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* newNode = (node*) malloc(sizeof(node));
    // bug 2: id-112, present, human, missing strdup
    newNode->item_name = item_name; 
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->next = NULL;

    if(*head == NULL) {
        *head = newNode;
        return EXIT_SUCCESS;
    } else if (pos == 0) {
        newNode->next = *head;
        *head = newNode;
        return EXIT_SUCCESS;
    } else {
        node* prev = NULL;
        node* curr = *head;
        while (pos-1 > 0) {
            prev = curr;
            curr = curr->next;
            pos--;
        }
        prev->next = newNode;
        newNode->next = curr;
        return EXIT_SUCCESS;
    }
    // bug 3: id-111, omitted, human, memory leak on EXIT_FAILURE
    return EXIT_FAILURE;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: id-483, omitted, approx-0.44, missing check for head == NULL
    // bug 2: id-484, omitted, approx-0.44, missing check for *head == NULL
    // bug 3: id-482, omitted, approx-0.44, missing check for next == NULL
    node* curr = *head;
    while (pos-1 > 0) {
        curr = curr->next;
        pos--;
    }
    // bug 4: id-481, omitted, approx-0.44, missing free
    // bug 5: id-480, omitted, approx-0.44, missing strdup
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: id-578, human, approx-0.44, missing check for head == NULL
    if(*head == NULL) {
        return EXIT_SUCCESS;
    } else if (pos == 1) {
        *head = (*head)->next;
        // bug 2: id-576, omitted, codex, missing free of item
        // bug 3: id-575, omitted, codex, missing free of item_name
        return EXIT_SUCCESS;
    } else {
        node* prev = NULL;
        node* curr = *head;
        while (pos-1 > 0) {
            prev = curr;
            curr = curr->next;
            // bug 6: id-577, omitted, codex, missing check for next == NULL
            pos--;
        }
        prev->next = curr->next;
        // bug 4: id-576, omitted, codex, missing free of item
        // bug 5: id-575, omitted, codex, missing free of item_name
        return EXIT_SUCCESS;
    }

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
    // bug 1: id-941, omitted, human, missing check for filename == NULL
    FILE *fptr = fopen(filename, "r");

    // bug 2: id-940, omitted, human, missing check for head == NULL
    node* curr = *head;
    while (curr != NULL) {
      curr = curr->next;
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fptr)) != -1) {
      char delim[] = ",";
      char *ptr = strtok(line, delim);
      // get three values, create new node, add to back of head
    }
    // bug 3: id-939, omitted, human, missing free of *line

    fclose(fptr);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // loop over the head note, create map of frequencies

    return EXIT_SUCCESS;
}


