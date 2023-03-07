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
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-224, omitted, human, does not check if a item_name is NULL before print
    // bug 2: id-225, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    if (head == NULL || str == NULL) {
        return EXIT_FAILURE;
    }
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    // bug 3: id-223, present, human, spurious free of str will cause double-free or other corruption
    free(str);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    int i = 0; char* str = malloc(MAX_ITEM_PRINT_LEN);
    node* cur = head;
    while (cur != NULL) {
        // bug 1: id-340, present, approx-0.47, doesn't check return value of list_item_to_string
        list_item_to_string(cur, str);
        // bug 2: id-341, omitted, approx-0.47, maybe uninit str 
        printf("%d: %s\n", i, str);
        i++;
        cur = cur->next;
    }
    free(str);
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    // bug 1: id-80, omitted, codex, missing check for head == NULL
    node* cur = *head;
    if(pos == 0) {
        *head = malloc(sizeof(node));
        (*head)->quantity = quantity;
        (*head)->price = price;
        // bug 2: id-81, omitted, codex, missing check for item_name == NULL
        (*head)->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
        strcpy((*head)->item_name, item_name);
        (*head)->next = cur;
        return EXIT_SUCCESS;
    }

    if (pos > 0) {
        if (cur == NULL) {
            return EXIT_FAILURE;
        }
        for (unsigned int i = 1; i < pos; i++) {
            if (cur->next == NULL) {
                return EXIT_FAILURE;
            }
            cur = cur->next;
        }
    }
    node* new = malloc(sizeof(node));
    new->quantity = quantity;
    new->price = price;
    // bug 3: id-81, omitted, codex, missing check for item_name == NULL
    new->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
    strcpy(new->item_name, item_name);
    new->next = cur->next;
    cur->next = new;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    if (head == NULL || *head == NULL) {
        return EXIT_FAILURE;
    }
    node* cur = *head;
    if (pos == 0) {
        cur->quantity = quantity;
        cur->price = price;
        // bug 1: id-456, present, codex, out of bounds write
        strcpy(cur->item_name, item_name);
        return EXIT_SUCCESS;
    }
    for (unsigned int i = 0; i < pos; i++) {
        if (cur->next == NULL) {
            return EXIT_FAILURE;
        }
        cur = cur->next;
    }
    cur->quantity = quantity;
    cur->price = price;
    // bug 2: id-456, present, human, out of bounds write
    strcpy(cur->item_name, item_name);
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    if (head == NULL || *head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos == 0) {
        // bug 1: id-554, omitted, humanf, missing free of item
        // bug 2: id-553, omitted, humanf, missing free of item_name
        *head = (*head)->next;
        return EXIT_SUCCESS;
    }
    node* cur = *head;
    for (unsigned int i = 0; i < pos - 1; i++) {
        if (cur->next == NULL) {
            return EXIT_FAILURE;
        }
        cur = cur->next;
    }
    if (cur->next != NULL) {
        cur->next = cur->next->next;
        // bug 3: id-554, omitted, human, missing free of item
        // bug 4: id-553, omitted, human, missing free of item_name
    }
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    if (head == NULL || *head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    node* prev1 = NULL;
    node* cur1 = *head;
    for (unsigned int i = 0; i < pos1 - 1; i++) {
        if (cur1->next == NULL) {
            return EXIT_FAILURE;
        }
        prev1 = cur1;
        cur1 = cur1->next;
    }
    node* prev2 = NULL;
    node* cur2 = *head;
    for (unsigned int i = 0; i < pos2 - 1; i++) {
        if (cur2->next == NULL) {
            return EXIT_FAILURE;
        }
        prev2 = cur2;
        cur2 = cur2->next;
    }
    node* temp = cur1->next;
    cur1->next = cur2->next;
    cur2->next = temp;
    // bug 1: id-713, omitted, humanf, memory leak by failing to update head pointer
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL || pos == NULL) return EXIT_FAILURE;
    node* cur = head;
    int max_price = 0;
    while (cur != NULL) {
        // bug 1: id-623, present, human, int vs float confusion
        if (cur->price > max_price) max_price = cur->price;
        cur = cur->next;
    }
    pos = &max_price;
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) return EXIT_FAILURE;
    node* cur = head;
    float total_cost = 0;
    while (cur != NULL) {
        total_cost += cur->quantity*cur->price;
        cur = cur->next;
    }
    total = &total_cost;
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE * file;
    // bug 1: id-835, omitted, human, missing check for filename == NULL
    file = fopen(filename, "w");
    node * cur = head;
    if (file == NULL) return EXIT_FAILURE;
    while (cur != NULL) {
        // bug 2: id-834, present, human, missing check for fprintf failure
        // bug 3: id-836, omitted, human, missing check for item_name == NULL
        fprintf(file, "%s,%f,%d\n", cur->item_name, cur->price, cur->quantity);
        cur = cur->next;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE * file;
    // bug 1: id-926, omitted, human, missing check for filename == NULL
    file = fopen(filename, "r");
    if (file == NULL) return EXIT_FAILURE;
    // bug 2: id-925, omitted, human, missing check for head == NULL
    node * cur = *head;
    if (cur == NULL) return EXIT_FAILURE;
    while (cur->next != NULL) cur = cur->next;
    // bug 3: id-923, omitted, human, failure to initialize new_name
    char * new_name; int new_price; int new_quant;
    // bug 4: id-924, present, human, fscanf may not initialize all values
    while (fscanf(file, "%s,%d,%d\n", new_name, &new_price, &new_quant) > 0) {
        node * new = malloc(sizeof(node));
        // bug 5: id-922, present, humanf, missing strdup
        new->item_name = new_name;
        new->price = new_price;
        new->quantity = new_quant;
        cur->next = new;
        new->next = NULL;
        cur = cur->next;
        // bug 6: id-921, omitted, human, leaks file descriptor on EXIT_FAILURE
        if (cur == NULL) return EXIT_FAILURE;
    }
    if (fscanf(file, "%s,%d,%d\n", new_name, &new_price, &new_quant) < 0) return EXIT_FAILURE;
    fclose(file);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // two iter nodes. one to go through and another to find duplicates for each node. 
    // when dup found, remove

    // bug 1: id-767, omitted, human, missing check for head == NULL
    node * main = *head;
    node * findDup = *head;
    int count = 0;
    int dupCount;

    
    if (main == NULL || findDup == NULL) return EXIT_FAILURE;

    while (main->next != NULL) {
        findDup = *head;
        dupCount = 0;
        // bug 2: id-766, omitted, human, missing check for next == NULL
        while (findDup->item_name != main->next->item_name) {
            findDup = findDup->next;
            dupCount ++;
        }
        if (dupCount <= count) { // found duplicate
            findDup->quantity += main->next->quantity;
            main->next = main->next->next;
        } // else did not find duplicate
        main = main->next;
        count++;
    }

    return EXIT_SUCCESS;
}


