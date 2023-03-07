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
    // bug 1: id-243, omitted, human, missing check for str == NULL
    // bug 2: id-244, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-245, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = head;
    int pos = 1;
    while (curr != NULL) {
        printf("%d: ", pos);
        char str[MAX_ITEM_PRINT_LEN];
        // bug 1: id-353, omitted, codex, doesn't check return value of list_item_to_string
        list_item_to_string(curr, str);
        // bug 2: id-354, omitted, codex, maybe uninit str
        printf("%s\n", str);
        curr = curr->next;
        pos++;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-102, omitted, human, missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = *head;
    if (curr == NULL && pos == 1) {
        curr = malloc(sizeof(node));
        // bug 2: id-101, omitted, codex, missing strdup
        curr->item_name = item_name; 
        curr->price = price;
        curr->quantity = quantity;
        curr->next = NULL;
        *head = curr;
        return EXIT_SUCCESS;
    }
    if (curr == NULL && pos != 1) {
        return EXIT_FAILURE;
    }
    if (pos == 1) {
        *head = malloc(sizeof(node));
        if (*head == NULL) {
            return EXIT_FAILURE;
        }
        (*head)->quantity = quantity;
        (*head)->price = price;
        // bug 3: id-101, omitted, codex, missing strdup
        (*head)->item_name = item_name; 
        (*head)->next = curr;
        return EXIT_SUCCESS;
    }
    int pos_count = 1;
    while (pos_count < pos - 1) {
        if (curr->next == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
        pos_count++;
    }
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return EXIT_FAILURE;
    }
    new_node->quantity = quantity;
    new_node->price = price;
    // bug 4: id-101, omitted, approx-0.44, missing strdup
    new_node->item_name = item_name; 
    new_node->next = curr->next;
    curr->next = new_node;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-469, omitted, human, missing check for head == NULL
    node *curr = *head;
    if (curr == NULL){
        return EXIT_FAILURE;
    }
    if (pos == 1) {
        curr->quantity = quantity;
        curr->price = price;
        // bug 2: id-467, omitted, codex, missing free
        // bug 3: id-468, present, codex, missing strdup
        curr->item_name = item_name;
        return EXIT_SUCCESS;
    }
    int pos_count = 1;
    while (pos_count < pos - 1) {
        if (curr->next == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
        pos_count++;
    }
    curr->quantity = quantity;
    curr->price = price;
    // bug 2: id-467, omitted, human, missing free
    // bug 3: id-468, present, human, missing strdup
    curr->item_name = item_name;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-564, omitted, human, missing check for head == NULL
    node* cur=*head;
    if (cur == NULL){
        return EXIT_FAILURE;
    }
    if (pos == 1){
        *head = cur->next;
        free(cur);
        // bug 2: id-563, omitted, codex, missing free of item_name
        return EXIT_SUCCESS;
    }
    int pos_count = 1;
    while (pos_count < pos - 1) {
        if (cur->next == NULL) {
            return EXIT_FAILURE;
        }
        cur = cur->next;
        pos_count++;
    }
    node* new_node = cur->next;
    cur->next = new_node->next;
    free(new_node);
    // bug 3: id-563, omitted, human, missing free of item_name
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-722, omitted, human, missing check for head == NULL
    if (*head == NULL){
        return EXIT_FAILURE;
    }
    if (pos1 > pos2){
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    node *curr1 = *head;
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    int pos_count=1;
    node *curr2 = *head;
    while(pos_count < pos1){
        if (curr1 == NULL){
            return EXIT_FAILURE;
        }
        curr1=curr1->next;
        curr2=curr2->next;
        pos_count++;
    }
    while(pos_count < pos2){
        if (curr2 == NULL){
            return EXIT_FAILURE;
        }
        curr2=curr2->next;
        pos_count++;
    }
    node *temp = curr1->item_name;
    curr1->item_name = curr2->item_name;
    curr2->item_name = temp;
    int tempval = curr1->quantity;
    curr1->quantity = curr2->quantity;
    curr2->quantity = tempval;
    float tempfloat=curr1->price;
    curr1->price = curr2->price;
    curr2->price = tempfloat;
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL){
       return EXIT_FAILURE; 
    }
    float tempmax = head->price;
    int maxid = 1;
    node *curr=head;
    int index=1;
    for (curr=head; curr!=NULL; curr=curr->next){
        if (curr->price > tempmax){
            tempmax=curr->price;
            maxid=index;
        }
        index++;
    }
    // bug 1: id-630, omitted, human, missing check for pos == NULL
    *pos=maxid;
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL)
    return EXIT_FAILURE;
    node *curr;
    // bug 1: id-664, omitted, human, missing check for total == NULL
    *total = 0;
    for (curr=head; curr; curr=curr->next){
        *total += curr->price * curr->quantity;
    }
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (!head || !filename){
        return EXIT_FAILURE;
    }
    FILE * fp = NULL;
    fp = fopen(filename, "w+");
    if (fp ==NULL){
        return EXIT_FAILURE;
    }
    node *curr;
    for (curr=head; curr; curr=curr->next){
        // bug 1: id-844, omitted, human, missing check for fprintf failure
        // bug 2: id-845, omitted, human, missing check for item_name == NULL
        fprintf(fp, "%s,%.2f,%d\n", curr->item_name, curr->price, curr->quantity);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (!head || !filename)
    {
        return EXIT_FAILURE;
    }
    FILE *fp = fopen(filename, "r");
    char line[MAX_ITEM_PRINT_LEN];
    char itemname[MAX_ITEM_PRINT_LEN];
    float price=0;
    int quantity=0;
    int count=1;
    // bug 2: id-933, omitted, human, missing check of return status for list_add_item_at_pos
    list_add_item_at_pos(head,"apple",0.80,2,1);
    list_add_item_at_pos(head,"banana",0.50,3,2);
    list_add_item_at_pos(head,"cheese",10.59,1,3);
    // bug 1: id-934, omitted, human, missing fclose
    return EXIT_SUCCESS;

    
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-768, omitted, human, missing check of return status for update_item_at_pos
    list_update_item_at_pos(head,"item1",1.0,11,1);
    list_remove_item_at_pos(head, 2);
    return EXIT_SUCCESS;
}


