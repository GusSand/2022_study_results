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
    // bug 1: missing check for str == NULL
    if (head != NULL) {
        // bug 2: uses sprintf instead of snprintf with MAX_ITEM_PRINT_LEN
        // bug 3: missing check for head->item_name
        sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    }
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    int counter = 1;
    while (head != NULL) {
        // bug 1: does not check if a item_name is NULL before print
        printf("%d: %d * %s @ $%.2f ea\n", counter, head->quantity, head->item_name, head->price);
        head = head->next;
        counter++;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 3: missing check for head == NULL
    node* n = *head;
    node* new_node = NULL;
    int counter = 1;

    if (pos == 1) {
        new_node = malloc(sizeof(struct _node));
        new_node->item_name = item_name; // bug 1: missing strdup
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = n;
        *head = new_node;
        return EXIT_SUCCESS;
    }

    while (n != NULL) {
        if (counter == pos-1) {
            new_node = malloc(sizeof(struct _node));
            new_node->item_name = item_name; // bug 2: missing strdup
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = n->next;
            n->next = new_node;
            return EXIT_SUCCESS;
        }
        n = n->next;
        counter++;
    }
    return EXIT_FAILURE;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    unsigned int counter = 1;
    // bug 2: missing check for head == NULL
    node* n = *head;
    while(n != NULL) {
        if (counter == pos) {
            // bug 1: missing free
            // bug 3: missing strdup
            n->item_name = item_name;
            n->price = price;
            n->quantity = quantity;
            return EXIT_SUCCESS;
        }
        n = n->next;
    }
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    node* n = *head;
    int counter = 1;

    if (pos == 1) {
        *head = n->next;
        // bug 2: missing free of item_name
        free(n);
        return EXIT_SUCCESS;
    }

    while (n != NULL) {
        if (counter == pos-1) {
            node* next_node = n->next;
            // bug 4: missing check for next == NULL
            n->next = next_node->next;
            // bug 3: missing free of item_name
            free(next_node);
            return EXIT_SUCCESS;
        }
        n = n->next;
        counter++;
    }

    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // bug 1: missing check for head == NULL
    node* n = *head;
    node* pos1_parent = NULL;
    node* pos2_parent = NULL;

    if (pos1 < 1 || pos2 < 1) return EXIT_FAILURE;
    if (pos1 == pos2) return EXIT_SUCCESS;

    pos1 = (pos1 < pos2) ? pos1 : pos2;
    pos2 = (pos2 < pos1) ? pos1 : pos2;

    int counter = 1;
    while(n != NULL) {
        if (counter == pos1-1) {
            pos1_parent = n;
        }
        if (counter == pos2-1) {
            pos2_parent = n;
        }
        n = n->next;
        counter++;
    }

    if (pos2_parent == NULL) return EXIT_FAILURE;

    node* node1 = NULL;
    node* node2 = pos2_parent->next;

    if (pos1_parent == NULL) {
        node1 = *head;
        *head = node2;
    }
    else {
        node1 = pos1_parent->next;
        pos1_parent->next = node2;
    }

    pos2_parent->next = node1;

    node* temp = node2->next;
    node2->next = node1->next;
    node1->next = temp;

    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    int counter = 0;
    // bug 2: int vs float confusion
    int max = -1;

    while (head != NULL) {
        counter++;

        if (head->price > max) max = head->price;
        head = head->next;
    }

    // bug 1: missing check for pos == NULL
    *pos = counter;

    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    float sum = 0;

    while (head != NULL) {
        sum += head->price * head->quantity;
        head = head->next;
    }

    // bug 1: missing check for total == NULL
    *total = sum;

    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    FILE* fileptr = NULL;

    // bug 1: missing check for filename == NULL
    fileptr = fopen(filename, "w");

    if (fileptr == NULL ) {
        return EXIT_FAILURE;
    }

    while (head != NULL) {
        // bug 2: missing check for fprintf failure
        // bug 3: missing check for item_name == NULL
        fprintf(fileptr, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }

    fclose(fileptr);

    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // bug 1: memory leak overwriting head pointer
    list_init(head);

    FILE* fileptr = NULL;
    char* line;
    size_t size = MAX_ITEM_PRINT_LEN;

    // bug 2: missing check for filename == NULL
    if((fileptr = fopen(filename, "r")) == NULL) {
        return EXIT_FAILURE;
    }

    char* item_name;
    float price;
    int quantity;
    int pos = 1;

    // bug 3: use of uninitialized line ptr
    while (getline(&line, &size, fileptr) != -1) {
        // bug 4: missing check for strtok returning NULL
        item_name = strtok(line, ",");
        // bug 5: off by one allocating strlen (forgot null terminator)
        char* str = (char*)malloc(strlen(item_name));
        strcpy(str,item_name);
        price = atof(strtok(NULL, ","));
        quantity = atoi(strtok(NULL, ","));
        // bug 6: missing check of return status for list_add_item_at_pos
        list_add_item_at_pos(head, str, price, quantity, pos);
        pos++;
    }
    // bug 7: missing fclose

    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // bug 1: missing check for head == NULL
    node* n = *head;
    int pos_n = 1;

    while (n != NULL) {
        node* m = n->next;
        int pos_m = pos_n+1;
        while (m != NULL) {
            // bug 2: missing check for item_name == NULL
            if (strcmp(n->item_name, m->item_name) == 0) {
                n->quantity += m->quantity;
                // bug 3: missing check of return status for remove_item_at_pos
                list_remove_item_at_pos(head, pos_m);
            }
            // bug 4: use-after-free
            m = m->next;
            pos_m++;
        }
        n = n->next;
        pos_n++;
    }

    return EXIT_SUCCESS;
}


