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

// Auxiliary functions

char* memRealloc(char* buffer, int oldSize, int newSize) {
    char* newBuffer = malloc(newSize);
    // bug 6: id-894, present, human, buffer overflow if oldSize > newSize
    for(int i = 0; i < oldSize; i++)
        newBuffer[i] = buffer[i];
    // bug 4: id-891, omitted, human, memory leak failing to free buffer
    return newBuffer;
}

// Main API functions

int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

int list_item_to_string(node *head, char *str) {
    // if head is not NULL, set str to contents of the node
    if (head) {
        // bug 1: id-160, omitted, approx-0.49, missing check for str == NULL
        // bug 2: id-161, omitted, approx-0.49, does not check if a item_name is NULL before print
        // bug 3: id-162, present, approx-0.49, Use of sprintf instead of snprintf for str with MAX_LEN
        sprintf(str, "%d * %s @ $%0.2f ea", head->quantity, head->item_name, head->price);
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

int list_print(node *head) {
    char str[100];
    if(head == NULL) {
        return EXIT_FAILURE;
    }
    // print each item in the list as a string
    node* curr = head;
    int pos = 1;
    while(curr != NULL) {
        // bug 1: id-302, present, human, doesn't check return value of list_item_to_string
        list_item_to_string(curr, str);
        // bug 2: id-302, omitted, human, maybe uninitialized str
        printf("%d: %s\n", pos, str);
        curr = curr->next;
        pos ++;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-22, omitted, human, missing check for head == NULL
    // if pos is 1 assign head to new node
    if(pos == 1) {
        node *new_node = malloc(sizeof(node));
        // bug 2: id-21, present, codex, sizeof(pointer) instead of strlen
        new_node->item_name = malloc(sizeof(item_name));
        // bug 4: id-22, omitted, codex, missing check for item_name == NULL
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
    // bug 3: id-21, present, codex, sizeof(pointer) instead of strlen
    new_node->item_name = malloc(sizeof(item_name));
    // bug 5: id-22, omitted, codex, missing check for item_name == NULL
    strcpy(new_node->item_name, item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = current->next;
    current->next = new_node;

    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: id-398, omitted, human, missing check for head == NULL
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

    // bug 2: id-396, omitted, human, missing free
    // bug 3: id-397, present, human, missing strdup
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos) {
    if(head == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: id-510, omitted, human, missing check for *head == NULL
    if(pos == 1) {
        // bug 2: id-509, omitted, human, memory leak, missing free()
        // bug 3: id-508, omitted, human, missing free of item_name
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
    // bug 4: id-508, omitted, human, missing free of item_name
    free(next);
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // bug 1: id-686, omitted, human, missing check for head == NULL
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

int list_find_highest_price_item_position(node *head, int *pos){
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    // bug 1: id-610, omitted, human, missing check for pos == NULL
    // bug 2: id-611, present, human, int vs float confusion
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

int list_cost_sum(node *head, float *total) {
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    // bug 1: id-650, omitted, humanf, missing check for total == NULL
    *total = 0;
    node* curr = head;
    while(curr != NULL) {
        *total += curr->price * curr->quantity;
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename) {
    if(head == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: id-805, omitted, human, missing check for filename == NULL
    FILE* f = fopen(filename, "w");
    if(f == NULL) {
        return EXIT_FAILURE;
    }

    node* curr = head;
    while(curr != NULL) {
        // bug 2: id-804, present, human, missing check for fprintf failure
        // bug 3: id-806, omitted, human, missing check for item_name == NULL
        fprintf(f, "%s,%0.2f,%d\n", curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }

    fclose(f);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename) {
    // bug 1: id-892, omitted, human, missing check for head == NULL
    // bug 2: id-890, present, human, memory leak overwriting head pointer 
    *head = NULL; 

    // bug 3: id-893, omitted, human, missing check for filename == NULL
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
            // bug 5: id-888, omitted, human, does not ensure str is null-terminated
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
                // bug 7: id-889, present, human, missing check of return status for list_add_item_at_pos
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

int list_deduplicate(node **head) {
    // bug 1: id-747, omitted, human, missing check for head == NULL
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
            // bug 2: id-748, omitted, human, missing check for item_name == NULL
            if(0 == strcmp(itr->item_name, curr->item_name)){
                int q1 = itr->quantity;
                int q2 = curr->quantity;
                int newQ = q1+q2;
                // bug 3: id-745, present, human, missing check of return status
                list_update_item_at_pos(head, itr->item_name, itr->price, newQ, i);
                list_remove_item_at_pos(head, range);
                break;
            }
            // bug 4: id-746, present, human, use-after-free
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


