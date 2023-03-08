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
    if(pos<0){
        return EXIT_FAILURE;
    }

    node* curr = *head;

    if(pos==1){
        node* newnode = malloc(sizeof(node));
        newnode->item_name = item_name;
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
                newnode->item_name = item_name;
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

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos<0){
        return EXIT_FAILURE; 
    }

    node* curr = *head;
    int n = 1;
    while(curr){
        if(n==pos){
            // node* newnode = malloc(sizeof(node));
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

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
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

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
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

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    float maxtillnow = head->price;

    node* curr = head->next;
    int n=2;
    while(curr){
        if(curr->price > maxtillnow){
            maxtillnow = curr->price;
            *pos = n;
        }

        curr = curr->next;
        n += 1;
    }

    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    *total = 0;
    node* curr = head;

    while(curr){
        *total += curr->price * curr->quantity;
        curr = curr->next;
    }

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

    FILE *fptr;
    fptr = fopen(filename, "w");

    if (fptr == NULL){
        return EXIT_FAILURE;
    }

    node* curr = head;

    while(curr){
        char str[100];

        // list_item_to_string(curr, str);
        int res = sprintf(str, "%s,%.2f,%d", curr->item_name, curr->price, curr->quantity);

        if (res < 0){
            return EXIT_FAILURE;
        }

        fprintf(fptr, "%s\n", str);

        curr = curr->next;
    }
    
    fclose(fptr);

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

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int len=0;
    node* curr = *head;

    while(curr){
        curr = curr->next;
        len += 1;
    }

    char* names[len+1];
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

    *head = NULL;
    list_init(head);
    for(int i=0; i<len; i++){
        if(names[i] != 0){
            list_add_item_at_pos(head, names[i], prices[i], quantities[i], i+1);
        }
    }

    // list_print(*head);

    return EXIT_SUCCESS;
}

