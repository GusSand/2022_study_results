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
    if(head == NULL){
        return EXIT_SUCCESS;
    }
    sprintf(str, "%d * %s @ $%0.2f ea", head->quantity, head->item_name, head->price);
    // if(!){
    //     return EXIT_FAILURE;
    // }
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;
    while(head){
        char buffer[100];
        // bug 1: doesn't check return value of list_item_to_string
        list_item_to_string(head, buffer);
        // bug 2: maybe uninit buffer
        printf("%d: %s\n", i, buffer);
        i++;
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
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
    new_node->item_name = item_name; // bug 2: missing strdup
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;

    if(_prev){
        _prev->next = new_node;
    }
    new_node->next = _head;

    if(pos==1){
        *head = new_node; // bug 3: memory leak by failing to update head (pos == 2, empty list)
    }

    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;
    // bug 1: missing check for head == NULL
    node* _head = *head;
    while(_head && i < pos){
        i++;
        _head = _head->next;
    }
    if(!_head && i < pos){
        return EXIT_FAILURE;
    }

    // bug 2: missing free
    // bug 3: missing strdup
    _head->item_name = item_name;
    _head->price = price;
    _head->quantity = quantity;

    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;

    // bug 1: missing check for head == NULL
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
        // bug 2: missing free of item
        // bug 3: missing free of item_name
        return EXIT_SUCCESS;
    }

    _prev->next = _head->next;
    // bug 4: missing free of item
    // bug 5: missing free of item_name
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;

    // bug 1: missing check for head == NULL
    node* _head1 = *head;
    node* _prev1 = NULL;
    int small_pos = pos1 < pos2 ? pos1 : pos2;
    int large_pos = pos1 > pos2 ? pos1 : pos2;

    // bug 2: missing check for head* == NULL
    while(_head1->next && i < small_pos){
        i++;
        _prev1 = _head1;
        _head1 = _head1->next;
    }

    i = 1;
    node* _head2 = *head;
    node* _prev2 = NULL;
    // bug 3: missing check for head* == NULL
    while(_head2->next && i < large_pos){
        i++;
        _prev2 = _head2;
        _head2 = _head2->next;
    }

    // bug 4: missing check for cursor == NULL
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

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    node* _head = head;
    float max_price = head->price;
    // bug 2: missing check for pos == NULL
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

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for total == NULL
    *total = 0.0;
    node* _head = head;
    while(_head){
        *total += (_head->price * _head->quantity);
        _head = _head->next;
    }
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* _head = head;
    if(!_head){
        return EXIT_FAILURE;
    }

    FILE* fp;
    // bug 1: missing check for filename == NULL
    fp = fopen(filename, "a+");

    if(!fp){
        return EXIT_FAILURE;
    }

    while(_head){
        // bug 2: missing check for fprintf failure
        // bug 3: missing check for item_name == NULL
        fprintf(fp, "%s,%0.2f,%d\n",_head->item_name, _head->price, _head->quantity);
        _head = _head->next;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    node* _head = *head;
    while(_head && _head->next){
        _head = _head->next;
    }
    FILE* fp;
    // bug 2: missing check for filename == NULL
    fp = fopen(filename, "r");

    if(!fp){
        return EXIT_FAILURE;
    }

    char line[100];

    while(fgets(line, 100, fp) != NULL){
        char* tmp;
        node* new_node = (struct _node*) malloc(sizeof(struct _node));
        // bug 3: strtok returning NULL will cause undefined behavior
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

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    node* _head1 = *head;
    while(_head1 && _head1->next){
        node* _head2 = _head1->next;
        node* _prev = _head1;
        while(_head2){
            int to_free = 0;
            // bug 2: missing check for item_name == NULL
            if(!strcmp(_head1->item_name, _head2->item_name)){
                _head1->quantity += _head2->quantity;
                _prev->next = _head2->next;
                to_free = 1;
            }
            if(to_free){
                node* tmp = _head2;
                _head2 = _head2->next;
                // bug 3: missing free of item_name
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


