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
    // bug 1: id-270, omitted, human, does not check if a item_name is NULL before print
    // bug 2: id-271, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    if ((head == NULL) || (str == NULL)){
        return EXIT_FAILURE;
    }
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    int i = 1;
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *current = head;
    while (current != NULL) {
        char str[MAX_ITEM_PRINT_LEN];
        if (list_item_to_string(current, str) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
        printf("%d: %s\n", i, str);
        i++;
        current = current->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    node *newNode = (node*)malloc(sizeof(node));
    // bug 2: id-125, present, human, missing strdup
    newNode->item_name = item_name; 
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->next = NULL;
    if ((head == NULL) || (*head == NULL)){
        // bug 1: id-126, omitted, human, wrong check for head == NULL
        *head = newNode; 
        return EXIT_SUCCESS;
    }
    node *current = *head;
    int i = 1;
    while (i < pos-1 && current->next != NULL){
        current = current->next;
        i++;
    }
    if (i == pos-1){
        newNode->next = current->next;
        // bug 3: id-124, present, human, memory leak by failing to update *head (pos == 3, len(list) == 1)
        current->next = newNode; 
    }
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if ((head == NULL) || (*head == NULL)){
        return EXIT_FAILURE;
    }
    node *current = *head;
    int i = 1;
    while (i < pos && current != NULL){
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: id-494, omitted, approx-0.34, missing free
    // bug 2: id-495, present, approx-0.34, missing strdup
    current->item_name = item_name;
    current->price = price;
    current->quantity = quantity;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos) {    
    if ((head == NULL) || (*head == NULL)) {
        return EXIT_FAILURE;
    }
    int i = 1;
    node *current = *head;
    node *prev = NULL;
    while (i < pos && current != NULL) {
        prev = current;
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    if (prev == NULL) {
        *head = current->next;
        // bug 1: id-595, omitted, human, missing free of item
        // bug 2: id-594, omitted, human, missing free of item_name
    } else {
        prev->next = current->next;
        // bug 3: id-595, omitted, human, missing free of item
        // bug 4: id-594, omitted, human, missing free of item_name
    }
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    if ((head == NULL) || (*head == NULL) || (pos1 == 0) || (pos2 == 0)) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    } else if (pos1 > pos2) {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    int i = 1;
    node *current = *head;
    while (i < pos1 && current != NULL) {
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    node *item1 = current;
    while (i < pos2 && current != NULL) {
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    node *item2 = current;
    int temp_quantity = item1->quantity;
    float temp_price = item1->price;
    char *temp_item_name = item1->item_name;
    item1->quantity = item2->quantity;
    item1->price = item2->price;
    item1->item_name = item2->item_name;
    item2->quantity = temp_quantity;
    item2->price = temp_price;
    item2->item_name = temp_item_name;
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) {
    if ((head == NULL) || (pos == 0)) {
        return EXIT_FAILURE;
    }
    float max_price = 0.0;
    int max_pos = 0;
    int i = 1;
    node *current = head;
    while (current != NULL) {
        if (current->price > max_price) {
            max_price = current->price;
            max_pos = i;
        }
        current = current->next;
        i++;
    }
    *pos = max_pos;
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total) {
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    float total_cost = 0.0;
    node *current = head;
    while (current != NULL) {
        total_cost += current->quantity * current->price;
        current = current->next;
    }
    // bug 1: id-674, omitted, human, missing check for total == NULL
    *total = total_cost;
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    if ((head == NULL) || (filename == NULL)) {
        return EXIT_FAILURE;
    }
    FILE *ptr = fopen(filename, "w");
    // bug 1: id-859, omitted, human, missing check for fopen failure
    node *current = head;
    while (current != NULL) {
        char str[MAX_ITEM_PRINT_LEN] = "";
        // bug 2: id-861, present, approx-0.42, buffer overflow
        // bug 3: id-860, omitted, approx-0.42, missing check for item_name == NULL
        sprintf(str, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
        // bug 4: id-859, omitted, human, missing check for fwrite failure
        fwrite(str, strlen(str), 1, ptr);
        current = current->next;
    }
    fclose(ptr);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename) {
    if (filename == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: id-955, omitted, approx-0.31, missing check for head == NULL
    node *current = *head;
    if ((current != NULL) && (current->next != NULL)) {
        current = current->next;
    }
    FILE *ptr = fopen(filename, "r");
    // bug 2: id-954, omitted, human, missing check for fopen failure
    char line[MAX_ITEM_PRINT_LEN];
    while (fgets(line, sizeof(line), ptr)) {
        line[strcspn(line, "\n")] = 0;
        node *newNode = (node*)malloc(sizeof(node));
        // bug 3: id-956, omitted, human, strtok returning NULL can cause undefined behavior
        newNode->item_name = strdup(strtok(line, ","));
        newNode->price = atof(strtok(NULL, ","));
        newNode->quantity = atoi(strtok(NULL, ","));
        newNode->next = NULL;
        if (*head == NULL) {
            *head = newNode;
            current = *head;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }
    fclose(ptr);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) {
    if ((head == NULL) || (*head == NULL)) {
        return EXIT_FAILURE;
    }
    node *current = *head;
    node *possible_dup = NULL;
    node *prev_possible_dup = NULL;
    while (current != NULL) {
        possible_dup = current->next;
        prev_possible_dup = current;
        while (possible_dup != NULL) {
            // bug 1: id-787, omitted, human, missing check for item_name == NULL
            if (strcmp(current->item_name, possible_dup->item_name) == 0) {
                // doesn't say to check if the prices are same or not
                current->quantity += possible_dup->quantity;
                prev_possible_dup->next = possible_dup->next;
            }
            prev_possible_dup = possible_dup;
            possible_dup = possible_dup->next;
            // bug 2: id-786, omitted, human, missing free of item
            // bug 3: id-785, omitted, human, missing free of item_name

        }
        current = current->next;
    }
    return EXIT_SUCCESS;
}


