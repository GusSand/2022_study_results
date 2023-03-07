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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL){
        return EXIT_FAILURE;
    }

    // char* iname = head->item_name;
    // char* quantity = (char *) head->quantity ;
    // char* price = head->price;

    int res = sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);

    if (res < 0){
        return EXIT_FAILURE;
    }

    else{
        return EXIT_SUCCESS;
    }
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if(head == NULL){
        return EXIT_FAILURE;
    }

    node* curr = head;

    int n = 1;
    while(curr){
        char str[256];
        int res = list_item_to_string(curr, str);

        if(res == EXIT_FAILURE){
            return EXIT_FAILURE;
        }
        // printf(s);
        printf("%d: %s\n", n, str);
        curr = curr->next;
        n += 1;
    }

    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos<0){
        return EXIT_FAILURE;
    }

    node* curr = *head;

    if(pos==1){
        node* newnode = malloc(sizeof(node));
        newnode->item_name = item_name; // bug 2: missing strdup
        newnode->price = price;
        newnode->quantity = quantity;
        
        newnode->next= *head;
        *head = newnode;
    }

    else{
        int n = 1;
        while(curr){
            if(n==pos-1){
                node* newnode = malloc(sizeof(node));
                newnode->item_name = item_name; // bug 3: missing strdup
                newnode->price = price;
                newnode->quantity = quantity;
                newnode->next= curr->next;

                curr->next = newnode;
                break;
            }

            else{
                // *head = (*head)->next;
                curr = curr->next;
                n += 1;
            }
        }
    }

    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos<0){
        return EXIT_FAILURE; 
    }

    // bug 1: missing check for head == NULL
    node* curr = *head;
    int n = 1;
    while(curr){
        if(n==pos){
            // node* newnode = malloc(sizeof(node));
            // bug 2: missing free
            // bug 3: missing strdup
            curr->item_name = item_name;
            curr->price = price;
            curr->quantity = quantity;
            // newnode->next= curr->next;

            // curr->next = newnode;
            return EXIT_SUCCESS;
            // break;
        }

        else{
            curr = curr->next;
            n += 1;
        }

    }

    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos<0){
        return EXIT_FAILURE;
    }

    node* curr = *head;

    if(pos==1){
        // node* newnode = malloc(sizeof(node));
        // newnode->item_name = item_name;
        // newnode->price = price;
        // newnode->quantity = quantity;
        
        // newnode->next= *head;
        // *head = newnode;
        *head = curr->next;
        // bug 2: missing free of item
        // bug 3: missing free of item_name
    }

    else{
        int n = 1;
        while(curr){
            if(n==pos-1){
                // node* newnode = malloc(sizeof(node));
                // newnode->item_name = item_name;
                // newnode->price = price;
                // newnode->quantity = quantity;
                // newnode->next= curr->next;

                // curr->next = newnode;
                curr->next = curr->next->next;
                // bug 4: wrong check for next == NULL
                // bug 5: missing free of item
                // bug 6: missing free of item_name
                break;
            }

            else{
                // *head = (*head)->next;
                curr = curr->next;
                n += 1;
            }
        }
    }

    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    node* curr = *head;
    int flag1 = 0;
    int flag2 = 0;

    int n=1;
    char* item1, *item2;
    float price1, price2;
    int q1, q2;
    node *next1, *next2;

    while(curr){
        if(n==pos1){
            item1 = curr->item_name;
            price1 = curr->price;
            q1 = curr->quantity;
            node* next1 = curr->next;
            flag1 = 1;
        }

        if(n==pos2){
            item2 = curr->item_name;
            price2 = curr->price;
            q2 = curr->quantity;
            node* next2 = curr->next;
            flag2 = 1;
        }

        if(flag1==1 && flag2==1){
            list_update_item_at_pos(head, item1, price1, q1, pos2);
            list_update_item_at_pos(head, item2, price2, q2, pos1);

            return EXIT_SUCCESS;
        }
        
        else{
            curr = curr->next;
            n += 1;
        }
        
    }

    return EXIT_FAILURE;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    float maxtillnow = head->price;

    node* curr = head->next;
    int n=2;
    while(curr){
        if(curr->price > maxtillnow){
            maxtillnow = curr->price;
            // bug 2: missing check for pos == NULL
            *pos = n;
        }

        curr = curr->next;
        n += 1;
    }

    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for total == NULL
    *total = 0;
    node* curr = head;

    while(curr){
        *total += curr->price * curr->quantity;
        curr = curr->next;
    }

    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    FILE *fptr;
    // bug 1: missing check for filename == NULL
    fptr = fopen(filename, "w");

    if (fptr == NULL){
        return EXIT_FAILURE;
    }

    node* curr = head;

    while(curr){
        char str[100];

        // list_item_to_string(curr, str);
        // bug 2: buffer overflow on str
        // bug 3: missing check for item_name == NULL
        int res = sprintf(str, "%s,%.2f,%d", curr->item_name, curr->price, curr->quantity);

        if (res < 0){
            return EXIT_FAILURE;
        }

    
        // bug 4: missing check for fprintf failure
        fprintf(fptr, "%s\n", str);

        curr = curr->next;
    }
    
    fclose(fptr);

    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for filename == NULL
    FILE *fptr;
    fptr = fopen(filename, "r");

    if (fptr == NULL){
        return EXIT_FAILURE;
    }

    node* curr = NULL;
    
    int n=1;
    // while (fscanf(fptr, "%20[^,],%f[^,],%d", item_name, &price, &quantity) == 3){
    char line[256];

    while(fgets(line, 256, fptr)){
    // while (fscanf(fptr, "%20[^,],%20[^,],%d", item_name, price, &quantity) == 3){
    // while (fgets(line, sizeof(line), fptr)) {
    // while ((token = strsep(&str, ",")))
        // char *item_name = strtok(line, ",");
        // float price = atof(strtok(NULL, ","));
        // int quantity = atoi(strtok(NULL, ","));

        char* line1 = strdup(line);

        node* newnode = malloc(sizeof(node));
        newnode->item_name = (char*) strtok(line1, ",");
        // bug 2: strtok can return NULL
        newnode->price = atof(strtok(NULL, ","));
        newnode->quantity = atoi(strtok(NULL, ","));
        newnode->next = NULL;

        if(n==1){
            curr = newnode;
            *head = curr;
        }

        else{
            curr->next = newnode;
            curr = curr->next;
        }

        n += 1;
        // newnode->next= curr->next;
    }

    fclose(fptr);

    return EXIT_SUCCESS;
}


int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int len=0;
    // bug 1: missing check for head == NULL
    node* curr = *head;

    while(curr){
        curr = curr->next;
        len += 1;
    }

    char* names[len+1];
    // bug 2: sizeof a VLA is undefined behavior
    memset(names, 0, sizeof(names));

    int quantities[len+1];
    memset(quantities, 0, sizeof(quantities));

    float prices[len+1];
    int j=0;

    curr = *head;

    while(curr){
        // int pos =  find(curr->item_name, names);
        int pos = -1;
        for(int i=0; i<len; i++){
            if(names[i] == curr->item_name){
                pos = i;
                break;
            }
        }

        if(pos==-1){
            names[j] = curr->item_name;
            quantities[j] = curr->quantity;

            // char str[256];
            // sprintf(str, "%.2f", curr->price);
            // sscanf(str, "%f", &(prices[j]));
            // prices[j] = curr->price;

            float value = (int)(curr->price * 100 + .5);
            prices[j] =  (float)value / 100;

            // printf("%f\n", curr->price);
            // printf("%f\n", prices[j]);
            j += 1;
        }

        else{
            // names[pos] = curr->item_name;
            quantities[pos] += curr->quantity;
        }

        // printf("quantities_0: %d\n", quantities[0]);

        curr = curr->next;
    }

    // bug 3: memory leak by overwriting head pointer
    *head = NULL;
    list_init(head);
    for(int i=0; i<len; i++){
        if(names[i] != 0){
            // bug 4: missing check of return status for list_add_item_at_pos
            list_add_item_at_pos(head, names[i], prices[i], quantities[i], i+1);
        }
    }

    // list_print(*head);

    return EXIT_SUCCESS;
}


