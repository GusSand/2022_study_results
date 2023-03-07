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

node* get_item_at_pos(node** head, int pos) {
    node* curr = *head;
    int i = 1;
    while (curr != NULL) {
        if (i == pos) {
            return curr;
        }
        curr = curr->next;
        i++;
    }
    return NULL;
}

// Main API functions

int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

int list_item_to_string(node *head, char *str) {
    // bug 1: id-264, omitted, human, missing check for str == NULL
    // bug 2: id-265, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-266, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    // TODO: Implement this function
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    node* curr = head;
    char* str;
    int i = 1;
    while (curr != NULL) {
        str = malloc(MAX_ITEM_PRINT_LEN);
        // bug 1: id-365, omitted, approx-0.11, doesn't check return value of list_item_to_string
        list_item_to_string(curr, str);
        // bug 2: id-366, omitted, approx-0.11, maybe uninit str
        printf("%d: %s\n", i, str);
        free(str);
        i++;
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-120, omited, human, missing check for head == NULL
    node *item = malloc(sizeof(node));
    // bug 2: id-119, present, human, used sizeof on item_name
    char* temp = malloc(sizeof(item_name)); 
    strcpy(temp, item_name);
    item->item_name = temp;
    item->price = price;
    item->quantity = quantity;

    node *curr = *head;

    if (pos == 1) {
        item->next = *head;
        *head = item;
        return EXIT_SUCCESS;
    }

    for (unsigned int i = 1; i < pos-1; i++) {
        if (curr == NULL) {
            // bug 3: id-118, omitted, human, memory leak on EXIT_FAILURE
            return EXIT_FAILURE; 
        }
        curr = curr->next;
    }

    if (curr == NULL) {
        // bug 4: id-118, omitted, human, memory leak on EXIT_FAILURE
        return EXIT_FAILURE; 
    }

    item->next = curr->next;
    curr->next = item;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (pos < 1 || head == NULL) {
        return EXIT_FAILURE;
    }

    node *curr = *head;
    int i = 1;
    while (curr && i < pos - 1) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }

    node *item = malloc(sizeof(node));
    // bug 1: id-490, present, human, sizeof pointer
    char* temp = malloc(sizeof(item_name));
    strcpy(temp, item_name);
    // bug 2: id-489, omitted, human, missing free of item_name
    curr->item_name = temp;
    curr->price = price;
    curr->quantity = quantity;
    // bug 3: id-488, omitted, human, memory leak failing to free item
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    if(pos < 1 || head == NULL) {
        return EXIT_FAILURE;
    }

    // bug 1: id-584, omitted, human, missing check for *head == NULL
    node *curr = *head;
    node *prev = NULL;
    int i = 1;
    while (curr->next && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (i < pos) {
        return EXIT_FAILURE;
    }

    if (curr->next == NULL) {
        if (prev == NULL) {
            *head = NULL;
            // bug 2: id-582, present, human, memory leak by overwriting head pointer
        } else {
            prev->next = NULL;
        }
        free(curr);
        // bug 3: id-583, omitted, human, missing free of item_name
    } else {
        prev->next = curr->next;
        free(curr);
        // bug 4: id-583, omitted, human, missing free of item_name
    }
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    node* item1 = get_item_at_pos(head, pos1);
    node* item2 = get_item_at_pos(head, pos2);
    if (item1 == NULL || item2 == NULL) {
        return EXIT_FAILURE;
    }

    char* temp_item_name = item1->item_name;
    item1->item_name = item2->item_name;
    item2->item_name = temp_item_name;

    float temp_price = item1->price;
    item1->price = item2->price;
    item2->price = temp_price;

    int temp_quantity = item1->quantity;
    item1->quantity = item2->quantity;
    item2->quantity = temp_quantity;

    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = head;
    int i = 1;
    float highest = 0.0;
    while (curr != NULL) {
        if (curr->price > highest) {
            // bug 1: id-637, omitted, codex, missing check for pos == NULL
            *pos = i;
            highest = curr->price;
        }
        curr = curr->next;
        i++;
    }

    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    node* curr = head;
    // bug 1: id-671, omitted, human, missing check for total == NULL
    *total = 0;

    while (curr) {
        *total += (curr->quantity * curr->price);
        curr = curr->next;
    }

    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    FILE* fp;
    // bug 1: id-854, omitted, human, missing check for filename == NULL
    fp = fopen(filename, "w+");

    if (!fp) {
        return EXIT_FAILURE;
    }

    node* curr = head;

    while (curr) {
        // bug 2: id-853, omitted, approx-0.47, missing check for fprintf failure
        // bug 3: id-855, omitted, approx-0.47, missing check for item_name == NULL
        fprintf(fp, "%s,%.2f,%d\n",
            curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    FILE* fd;
    
    // bug 1: id-948, omitted, human, missing check for filename == NULL
    fd = fopen(filename, "r");

    if (!fd) {
        return EXIT_FAILURE;
    }

    // bug 2: id-950, present, human, potential buffer overflow if line is longer than 2048 chars
    char* curr_line = malloc(2048*sizeof(char));
    unsigned int i = 1;
    unsigned int n = 0;
    char* delim = ",";
    int c;
    
    while ((c = fgetc(fd)) != EOF) {
        if (c == '\n') {
            curr_line[n] = '\0';
            n = 0;

            char* arr[3];
            // bug 3: id-949, omitted, human, missing check for strtok returning NULL
            arr[0] = strtok(curr_line, delim);
            arr[1] = strtok(NULL, delim);
            arr[2] = strtok(NULL, delim);

            // bug 4: id-947, omitted, human,missing check of return status for list_add_item_at_pos
            list_add_item_at_pos(head, arr[0],
                atof(arr[1]), atoi(arr[2]), i++);
            curr_line[0] = '\0';
        } else {
            curr_line[n++] = (char)c;
        }
    }

    free(curr_line);
    fclose(fd);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    int capacity = 128;
    char** item_names = malloc(capacity*sizeof(char*));
    
    // bug 1: id-780, omitted, approx-0.45, missing check for head == NULL
    node *curr = *head;
    int pos = 1;

    while (curr) {
        if (pos >= capacity) {
            capacity *= 2;
            item_names = realloc(item_names, capacity*sizeof(char*));
        }

        int found = 0;

        for (unsigned int i = 0; i < pos - 1 && !found; ++i) {
            // bug 2: id-781, omitted, human, missing check for item_name == NULL
            // bug 3: id-779, omitted, human, id-potential use of uninitialized variable
            if (strcmp(curr->item_name, item_names[i]) == 0) {
                node* to_update = get_item_at_pos(head, i+1);
                // bug 4: id-778, present, human, use after free
                list_update_item_at_pos(head,
                    to_update->item_name,
                    to_update->price,
                    to_update->quantity + curr->quantity,
                    i+1);
                
                curr = curr->next;
                // bug 5: id-777, omitted, human, missing check of return status for remove_item_at_pos
                list_remove_item_at_pos(head, pos);
                found = 1;
            }
        }

        if (!found) {
            item_names[pos-1] = curr->item_name;
            pos++;
            curr = curr->next;
        }
    }

    return EXIT_SUCCESS;
}


