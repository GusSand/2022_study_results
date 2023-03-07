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
    // bug 2: does not check if a item_name is NULL before print
    // bug 3: Use of sprintf instead of snprintf for str with MAX_LEN
    // bug 4: missing check for head == NULL
    if(sprintf(str, "%i * %s @ $%.2f ea", head->quantity, head->item_name, head->price))
        return EXIT_SUCCESS;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_print(node *head) {
    int i = 1;
    while(1==1) {
        if(head!=NULL) {
            // bug 1: tempstr is too small
            char tempstr[32];
            // bug 2: doesn't check return value of list_item_to_string
            list_item_to_string(head, tempstr);
            // bug 3: maybe uninit tempstr
            printf("%i: %s\n",i,tempstr);
        }
        // bug 4: possible null pointer deref
        head = head->next;
        i++;
        if(head == NULL) {
            return EXIT_SUCCESS;
        }

    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: missing check for head == NULL
    if(pos<1)
        return EXIT_FAILURE;
    else{
        while(pos--) {
            if(pos==0){
                node * temp = (node*) malloc(sizeof(node));
                temp ->  item_name = item_name; // bug 2: missing strdup
                temp->price = price;
                temp->quantity = quantity;
                temp->next = *head;
                *head = temp; // bug 5: memory leak overwriting head
                return EXIT_SUCCESS;
            }
            else {
                head=&(*head)->next; // bug 4: type confusion head node **
            }
        }
    }
    // bug 3: missing check for next == NULL
    return EXIT_FAILURE;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: missing check for head == NULL
    unsigned int nextpos = pos+1;
    int pos2=pos+1;
    if(pos<1)
        return EXIT_FAILURE;
    else{
        while(pos--) {
            if(pos==0){
                node * temp = (node*) malloc(sizeof(node));
                // bug 4: missing strdup
                temp ->  item_name = item_name;
                temp->price = price;
                temp->quantity = quantity;
                temp->next = *head;
                // bug 5: memory leak overwriting head pointer
                *head = temp;
                list_remove_item_at_pos(head, pos2);
                return EXIT_SUCCESS;
            }
            else {
                // bug 2: missing check for *head == NULL
                // bug 3: missing check for next == NULL
                head=&(*head)->next;
            }
        }
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    node *temp = *head, *prev;
    int i = 1;
    if(temp!=NULL&&i==pos) {
        *head = temp->next;
        free (temp);
        // bug 2: missing free of item_name
        return EXIT_SUCCESS;
    }

    while(temp!=NULL&&i!=pos) {
        prev = temp;
        temp = temp->next;
    }
    if(temp==NULL) {
        return EXIT_SUCCESS;
    }
    prev->next = temp->next;
    free(temp);
    // bug 3: missing free of item_name
    return EXIT_SUCCESS;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    if(pos1==pos2)
        return EXIT_SUCCESS;

    // bug 1: missing check for head == NULL
    node *prev1 = NULL, *curr1 = *head;
    int i = 1;
    while(curr1 && i!=pos1) {
        prev1 = curr1;
        curr1 = curr1->next;
        i++;
    }
    node *prev2 = NULL, *curr2 = *head;
    i = 1;
    while(curr2 && i!=pos2) {
        prev2 = curr2;
        curr2 = curr2->next;
        i++;
    }
    if(curr1 == NULL || curr2 ==NULL) {
        return EXIT_SUCCESS;
    }
    if(prev1 != NULL) {
        prev1->next = curr2;
    }
    else{
        *head = curr2;}
    if(prev2 != NULL) {
        prev2->next = curr1;
    }
    else{
        *head = curr1;}
    node* temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;
    

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{

    int curr = 1;
    int high = 1;
    float val = 0;
    while(head != NULL) {
        if(head->price >val) {
            val = head->price;
            high = curr;
        }
        curr++;
        head=head->next;
    }
    // bug 1: missing check for pos == NULL
    *pos = high;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{

    float val = 0;
    while(head != NULL) {
        val = val + (head->price * head->quantity);
        head=head->next;
    }
    // bug 1: missing check for total == NULL
    *total = val;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{

    FILE *fptr;

    // bug 1: missing check for filename == NULL
    fptr = fopen(filename, "w");
    // bug 2: missing check for fopen failure
    while(head != NULL) {

        // bug 3: missing check for fprintf failure
        // bug 4: missing check for item_name == NULL
        fprintf(fptr,"%s,%.2f,%i\n", head->item_name, head->price, head->quantity);

        head=head->next;
    }
    fclose(fptr);

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename){
    node* curr;
    curr = *head;
    node* prev;
    prev = *head;
    FILE *fptr;
    // bug 1: missing check for head == NULL
    // bug 2: missing check for filename == NULL
    fptr = fopen(filename, "r");
    // bug 3: missing check for fopen failure
    float val;
    int quant;
    int pos = 1;
    while(curr != NULL) {
        prev = curr;
        curr=curr->next;
        pos++;
    }
    while(!feof(fptr)){
        // bug 4: buffer overflow fixed size buffer
        char* name = (char*) malloc(100 * sizeof(char));
        // bug 5: fscanf can fail to set all arguments
        fscanf(fptr,"%[^,],%f,%d ", name, &val, &quant);
        // bug 6: missing check of return status for list_add_item_at_pos
        list_add_item_at_pos(head, name, val, quant, pos);
        pos++;
        // bug 7: memory leak failing to free name
    }
    
    fclose(fptr);
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) {
    node* p1;
    node* p2;
    node* dup;
    int pos = 1;
    int pos1 = 1;
    // bug 1: missing check for head == NULL
    p1 = *head;
    while(p1 != NULL && p1->next != NULL) {
        p2 = p1;
        pos = pos1;
        while(p2 != NULL && p2->next != NULL) {
            // bug 2: missing check for item_name == NULL
            if(!strcmp(p1->item_name,p2->next->item_name)) {

                dup = p2->next;
                int sum = p1->quantity + p2->next->quantity;
                p1->quantity = p1->quantity + p2->next->quantity;


                if(dup->next == NULL){
                    p2->next=NULL;
                    break;
                }
                else {
                    p2->next=p2->next->next;
                }

                // bug 3: missing free of item_name
                free(dup);
                break;
                
            }
            else{
                p2=p2->next;
                pos++;
            }

        }
        if(p1->next==NULL) {
            break;
        }
        else {
            p1=p1->next;
        }
        pos1++;
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}


