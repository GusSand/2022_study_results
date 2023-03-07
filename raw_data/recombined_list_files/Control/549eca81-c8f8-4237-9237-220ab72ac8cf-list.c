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
    if(head == NULL){ return EXIT_FAILURE; }
    // bug 1: missing check for str == NULL
    // bug 2: does not check if a item_name is NULL before print
    int i = snprintf(str, MAX_ITEM_PRINT_LEN, "%u * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
    //return EXIT_FAILURE;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    char buffer[MAX_ITEM_PRINT_LEN];
    if(head == NULL){ return EXIT_FAILURE; }
    node *curr = head;
    // bug 3: infinite loop
    while(curr != NULL){
        // bug 1: doesn't check return value of list_item_to_string
        list_item_to_string(curr, buffer);
        // bug 2: maybe uninit buffer
        printf("%s\n", buffer);
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    node *nnode = malloc(sizeof(node));
    nnode->item_name = item_name; // bug 2: missing strdup
    nnode->price = price;
    nnode->quantity = quantity;
    if(pos == 1){
        nnode->next = *head;
    }
    else{
        node *curr = *head;
        for(unsigned int i = 2; i < pos; i++){
            if (curr == NULL){
                // bug 3: memory leak on EXIT_FAILURE
                return EXIT_FAILURE; //list shorter than pos
            }
            curr = curr->next;
        }
        nnode->next = curr->next;
        curr->next = nnode;
    }
    *head = nnode; // bug 4: memory leak by overwriting head pointer
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: missing check for head == NULL
    node *curr = *head;
    for(unsigned int i = 1; i < pos; i++){
        if(curr == NULL){
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    // bug 2: missing free
    // bug 3: missing strdup
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    if(pos == 1){
        node *temp = *head;
        *head = temp->next;
        free(temp);
        // bug 3: missing free of item_name
        return EXIT_SUCCESS;
    }
    else{
        node *curr = *head;
        for(int i = 2; i < pos; i++){
            if( curr == NULL ){ return EXIT_FAILURE; }
            curr = curr->next;
        }
        if(curr->next == NULL){ return EXIT_FAILURE; }
        node *temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
        // bug 4: missing free of item_name
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos1 == pos2){return EXIT_SUCCESS;}
    if(pos1 > pos2){int t = pos1; pos1=pos2; pos2=t;}
    if(pos1 < 1){return EXIT_FAILURE;}
    node *p1;
    node *p2;

    // bug 1: missing check for head == NULL
    node *curr = *head;
    for(int i = 1; i < pos2-1; i++){
        if (curr == NULL){
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    p2 = curr;
    if(pos1 == 1){
        p2->next = *head;
        *head = p2;
        
    }
 
 
    curr = *head;
    for(int i = 2; i < pos1-1; i++){
        if (curr == NULL){
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    p1 = curr;



    //if(p2->next == NULL){return EXIT_FAILURE;}
    
    if(pos2-pos1 == 1){
        // bug 2: missing check for next == NULL
        node *t = p2->next->next;
        p1->next = p2->next;
        p2->next->next = p2;
        p2->next = t;
    }
    else{
        // bug 3: missing check for next == NULL
        node *t = p1->next;
        p1->next = p2->next;
        p2->next = t;
        t = p1->next->next;
        p1->next->next = p2->next->next;
        p2->next->next = t;
    }
    // bug 4: memory leak (loses nodes)
    // bug 5: infinite loop

    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    //segfaults while commented and unable to debug
    // if(head == NULL){
    //     return EXIT_FAILURE;
    // }
    // int ind = 1;
    // int mpos = 1;
    // float max = 0;
    // node *d = head;
    // while(d != NULL){
    //     if(d->price > max){
    //         mpos = ind;
    //         max = d->price;
    //     }
    //     d = d->next;
    //     ind += 1;
    // }
    // return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    float tot = 0;
    node *curr = head;
    while(curr != NULL){
        tot += curr->price;
        curr = curr->next;
    }
    // bug 1: missing check for total == NULL
    *total = tot;
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for filename == NULL
    FILE *fptr = fopen(filename, "w");
    // bug 2: missing check for fopen failure
    char buf [100];
    node *curr = head;
    // bug 3: infinite loop
    while(curr != NULL){
        // bug 4: missing check for item_name == NULL
        int i = snprintf(buf, 100, "%s,%.2f,%d\n",head->item_name, head->price, head->quantity);
        // bug 5: missing check for fprintf failure
        fputs(buf, fptr);
    }
    fclose(fptr);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: missing check for filename == NULL
    FILE *fptr = fopen(filename, "r");
    // bug 2: missing check for fopen failure
    char buf [100];
    int pos = 1;
    while(fgets(buf, 100, fptr) != NULL){
        char t[100];
        strcpy(t,buf);
        char *pt;
        pt = strtok(t, ",");
        char *name = pt;
        // bug 3: missing check for strtok returning NULL causes undefined behavior (pt == NULL)
        pt = strtok(t, ",");
        float price = atof(pt);
        pt = strtok(t, ",\n");
        int quantity = atoi(pt);

        // bug 4: missing check of return status for list_add_item_at_pos
        list_add_item_at_pos(head, name, price, quantity, pos);
        pos ++;
    }

    // bug 5: fails to fclose

    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: missing check for head == NULL
    node *curr = *head;
    while(curr != NULL){
        node *c2 = curr;
        while(c2->next != NULL){
            if(c2->next->item_name == curr->item_name && c2->next->price == curr->price){
                curr->quantity += c2->next->quantity;
                node *t = c2->next;
                c2->next = c2->next->next;
                // bug 2: memory leak failing to free item
                // bug 3: memory leak failing to free item_name
            }
            c2 = c2->next;
        }
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}


