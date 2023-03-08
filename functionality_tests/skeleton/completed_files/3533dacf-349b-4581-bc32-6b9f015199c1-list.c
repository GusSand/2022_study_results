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
    // if head is not NULL, set str to contents of the node
    if (head) {
        sprintf(str, "%d * %s @ $%0.2f ea", head->quantity, head->item_name, head->price);
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
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
    char str[100];
    if(head == NULL) {
        return EXIT_FAILURE;
    }
    // print each item in the list as a string
    node* curr = head;
    int pos = 1;
    while(curr != NULL) {
        list_item_to_string(curr, str);
        printf("%d: %s\n", pos, str);
        curr = curr->next;
        pos ++;
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
    // if pos is 1 assign head to new node
    if(pos == 1) {
        node *new_node = malloc(sizeof(node));
        new_node->item_name = malloc(sizeof(item_name));
        strcpy(new_node->item_name, item_name);
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = *head;
        *head = new_node;
        return EXIT_SUCCESS;
    }

    // decrement pos until pos = 1
    node *current = *head;
    while (pos > 2 && current != NULL) {
        current = current->next;
        pos--;
    }

    if(current == NULL) {
        return EXIT_FAILURE;
    }

    // create node
    node *new_node = malloc(sizeof(node));
    new_node->item_name = malloc(sizeof(item_name));
    strcpy(new_node->item_name, item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = current->next;
    current->next = new_node;

    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if(*head == NULL) {
        return EXIT_FAILURE;
    }

    node* curr = *head;
    for(int i = 1; i < pos; i++) {
        curr = curr->next;
        if(curr == NULL) {
            return EXIT_FAILURE;
        }
    }

    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position *pos*
int list_remove_item_at_pos(node **head, int pos) {
    if(head == NULL) {
        return EXIT_FAILURE;
    }
    if(pos == 1) {
        *head = (*head)->next;
        return EXIT_SUCCESS;
    }
    node* curr = *head;
    for(int i = 1; i < pos - 1; i++) {
        curr = curr->next;
        if(curr == NULL) {
            return EXIT_FAILURE;
        }
    }
    if(curr->next == NULL) {
        return EXIT_FAILURE;
    }
    node* next = curr->next;
    curr->next = next->next;
    free(next);
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if(*head == NULL) {
        return EXIT_FAILURE;
    }
    node* prev1 = NULL;
    node* prev2 = NULL;
    node* curr1 = *head;
    node* curr2 = *head;

    // find the two nodes
    while(curr1 != NULL && pos1 > 1) {
        prev1 = curr1;
        curr1 = curr1->next;
        pos1--;
    }
    if(curr1 == NULL) {
        return EXIT_FAILURE;
    }
    while(curr2 != NULL && pos2 > 1) {
        prev2 = curr2;
        curr2 = curr2->next;
        pos2--;
    }
    if(curr2 == NULL) {
        return EXIT_FAILURE;
    }

    // swap nodes
    if(prev1 != NULL) {
        prev1->next = curr2;
    } else {
        *head = curr2;
    }
    if(prev2 != NULL) {
        prev2->next = curr1;
    } else {
        *head = curr1;
    }
    node* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;

    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos){
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    int maxPri = head->price;
    *pos = 1;
    node* curr = head;
    int currPos = 1;
    while(curr != NULL) {
        if(curr->price > maxPri) {
            *pos = currPos;
            maxPri = curr->price;
        }
        curr = curr->next;
        currPos ++;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    *total = 0;
    node* curr = head;
    while(curr != NULL) {
        *total += curr->price * curr->quantity;
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    if(head == NULL) {
        return EXIT_FAILURE;
    }
    FILE* f = fopen(filename, "w");
    if(f == NULL) {
        return EXIT_FAILURE;
    }

    node* curr = head;
    while(curr != NULL) {
        fprintf(f, "%s,%0.2f,%d\n", curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }

    fclose(f);
    return EXIT_SUCCESS;
}


// helper function
char* memRealloc(char* buffer, int oldSize, int newSize) {
    char* newBuffer = malloc(newSize);
    for(int i = 0; i < oldSize; i++)
        newBuffer[i] = buffer[i];
    return newBuffer;
}


// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    *head = NULL; 

    FILE* f = fopen(filename, "r");
    if(f == NULL) {
        return EXIT_FAILURE;
    }
    
    int bufSize = 5;
    int bytesRead = 0;

    char* buf = malloc(bufSize);
    int res = fread(buf, 1, bufSize, f);
    bytesRead += res;

    while(res > 0) {
        if(bytesRead == bufSize) {
            int oldSize = bufSize;
            bufSize *= 2;
            buf = memRealloc(buf, oldSize, bufSize);
        }

        res = fread(buf+bytesRead, 1, bufSize-bytesRead, f);
        bytesRead += res;
    }   

    int state = 0;
    int start = 0;
    int end = 0;
    int strSize = 20;
    int pos = 1;
    char* str = malloc(strSize);
    char* item_name;
    float price;
    int quantity = 0;
    for(int i = 0; i < bytesRead; i++) {
        if(buf[i] == ',' || buf[i] == '\n') {
            end = i;
            int newSize = end-start;

            if(i + 1 == bytesRead) newSize += 1;

            str = memRealloc(str, strSize, newSize);
            memmove(str, buf+start, newSize);
            strSize = newSize;
            start = end+1;

            if(state == 0) {
                item_name = str;
                state = 1;
            } else if(state == 1) {
                price = atof(str);
                state = 2;
            } else if(state == 2) {
                quantity = atoi(str);
                list_add_item_at_pos(head, item_name, price, quantity, pos);
                pos ++ ; 
                state = 0;
            }
        }
    }

    fclose(f);
    free(str);
    free(buf);
    return EXIT_SUCCESS;
}




// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    if(*head == NULL) {
        return EXIT_FAILURE;
    }

    node* curr = (*head)->next;
    node* prev = *head;
    int range = 2;
    while(curr != NULL) {
        node* itr = *head;
        int i;
        for(i = 1; i < range; i++) {
            if(0 == strcmp(itr->item_name, curr->item_name)){
                int q1 = itr->quantity;
                int q2 = curr->quantity;
                int newQ = q1+q2;
                list_update_item_at_pos(head, itr->item_name, itr->price, newQ, i);
                list_remove_item_at_pos(head, range);
                break;
            }
            itr = itr->next;
        }
        if(i == range) {
            curr = curr->next;
            range ++;
        } else {
            curr = prev->next;
        }
        
    }

    return EXIT_SUCCESS;
}