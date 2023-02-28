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
    if(head == NULL){
        return EXIT_SUCCESS;
    }
    sprintf(str, "%d * %s @ $%0.2f ea", head->quantity, head->item_name, head->price);
    // if(!){
    //     return EXIT_FAILURE;
    // }
    return EXIT_SUCCESS;
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
    int i = 1;
    while(head){
        char buffer[100];
        list_item_to_string(head, buffer);
        printf("%d: %s\n", i, buffer);
        i++;
        head = head->next;
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
    int i = 1;

    node* _head = *head;
    node* _prev = NULL;
    while(_head && i < pos){
        i++;
        _prev = _head;
        _head = _head->next;
    }

    node* new_node = (struct _node*) malloc(sizeof(struct _node));
    new_node->item_name = item_name;
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;

    if(_prev){
        _prev->next = new_node;
    }
    new_node->next = _head;

    if(pos==1){
        *head = new_node;
    }

    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;

    node* _head = *head;
    while(_head && i < pos){
        i++;
        _head = _head->next;
    }
    if(!_head && i < pos){
        return EXIT_FAILURE;
    }

    _head->item_name = item_name;
    _head->price = price;
    _head->quantity = quantity;

    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;

    node* _head = *head;
    node* _prev = NULL;
    while(_head && i < pos){
        i++;
        _prev = _head;
        _head = _head->next;
    }
    if(!_head && i < pos){
        return EXIT_FAILURE;
    }

    if(!_prev){
        *head = _head->next;
        return EXIT_SUCCESS;
    }

    _prev->next = _head->next;
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;

    node* _head1 = *head;
    node* _prev1 = NULL;
    int small_pos = pos1 < pos2 ? pos1 : pos2;
    int large_pos = pos1 > pos2 ? pos1 : pos2;

    while(_head1->next && i < small_pos){
        i++;
        _prev1 = _head1;
        _head1 = _head1->next;
    }

    i = 1;
    node* _head2 = *head;
    node* _prev2 = NULL;
    while(_head2->next && i < large_pos){
        i++;
        _prev2 = _head2;
        _head2 = _head2->next;
    }

    _prev2->next = _head1;
    node* tmp = _head1->next;
    _head1->next = _head2->next;
    _head2->next = tmp;
    if(_prev1){
        _prev1->next = _head2;
    }
    if(small_pos==1)
        *head = _head2;
    return EXIT_SUCCESS;    
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* _head = head;
    float max_price = head->price;
    *pos = 1;
    int i = 0;
    while(_head){
        i++;
        if(max_price < _head->price){
            max_price = _head->price;
            *pos = i;
        }
        _head = _head->next;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    *total = 0.0;
    node* _head = head;
    while(_head){
        *total += (_head->price * _head->quantity);
        _head = _head->next;
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
    node* _head = head;
    if(!_head){
        return EXIT_FAILURE;
    }

    FILE* fp;
    fp = fopen(filename, "a+");

    if(!fp){
        return EXIT_FAILURE;
    }

    while(_head){
        fprintf(fp, "%s,%0.2f,%d\n",_head->item_name, _head->price, _head->quantity);
        _head = _head->next;
    }
    fclose(fp);
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
    node* _head = *head;
    while(_head && _head->next){
        _head = _head->next;
    }
    FILE* fp;
    fp = fopen(filename, "r");

    if(!fp){
        return EXIT_FAILURE;
    }

    char line[100];

    while(fgets(line, 100, fp) != NULL){
        char* tmp;
        node* new_node = (struct _node*) malloc(sizeof(struct _node));
        tmp = strtok(line,",");
        new_node->item_name = (char*)malloc(strlen(tmp)+1);
        strcpy(new_node->item_name, tmp);

        tmp = strtok(NULL,",");
        new_node->price = atof(tmp);

        tmp = strtok(NULL,",");
        new_node->quantity = atoi(tmp);

        new_node->next = NULL;
        if(_head)
            _head->next = new_node;
        _head = new_node;
        if(*head == NULL){
            *head = new_node;
        }
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* _head1 = *head;
    while(_head1 && _head1->next){
        node* _head2 = _head1->next;
        node* _prev = _head1;
        while(_head2){
            int to_free = 0;
            if(!strcmp(_head1->item_name, _head2->item_name)){
                _head1->quantity += _head2->quantity;
                _prev->next = _head2->next;
                to_free = 1;
            }
            if(to_free){
                node* tmp = _head2;
                _head2 = _head2->next;
                free(tmp);
            } else {
                _prev = _head2;
                _head2 = _head2->next;
            }
        }
        _head1 = _head1->next;
    }   
    return EXIT_SUCCESS;
}

