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

// Note: All list_ functions return a status code EXIT_FAILURE or EXIT_SUCCESS
// to indicate whether the operation was successful or not.

// Members of the node struct:
// char* item_name, float price, int quantity, node *next

// create a new list
int list_init(node **head) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        *head = malloc(sizeof(node));
        if (*head == NULL) {
            return EXIT_FAILURE;
        }
        (*head)->next = NULL;
        return EXIT_SUCCESS;
    }
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        if (str == NULL) {
            return EXIT_FAILURE;
        } else {
            char *s = malloc(MAX_ITEM_PRINT_LEN);
            if (s == NULL) {
                return EXIT_FAILURE;
            }
            sprintf(s, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
            strcpy(str, s);
            free(s);
            return EXIT_SUCCESS;
        }
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
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = head;
        char *s = malloc(MAX_ITEM_PRINT_LEN);
        if (s == NULL) {
            return EXIT_FAILURE;
        }
        printf("%s", "");
        while (cur->next != NULL) {
            list_item_to_string(cur, s);
            printf("%s", s);
            printf("\n");
            cur = cur->next;
        }
        free(s);
        return EXIT_SUCCESS;
    }
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        if (pos == 0) {
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL) {
                return EXIT_FAILURE;
            }
            new_node->item_name = malloc(strlen(item_name) + 1);
            if (new_node->item_name == NULL) {
                return EXIT_FAILURE;
            }
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = *head;
            *head = new_node;
            return EXIT_SUCCESS;
        } else {
            node *cur = *head;
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL) {
                return EXIT_FAILURE;
            }
            new_node->item_name = malloc(strlen(item_name) + 1);
            if (new_node->item_name == NULL) {
                return EXIT_FAILURE;
            }
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = NULL;
            unsigned int k = 0;
            while (cur != NULL) {
                if (k == pos) {
                    new_node->next = cur->next;
                    cur->next = new_node;
                    return EXIT_SUCCESS;
                } else {
                    k++;
                    cur = cur->next;
                }
            }
            return EXIT_FAILURE;
        }
    }
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = *head;
        unsigned int k = 0;
        while (cur != NULL) {
            if (k == pos) {
                cur->item_name = malloc(strlen(item_name) + 1);
                if (cur->item_name == NULL) {
                    return EXIT_FAILURE;
                }
                strcpy(cur->item_name, item_name);
                cur->price = price;
                cur->quantity = quantity;
                return EXIT_SUCCESS;
            } else {
                k++;
                cur = cur->next;
            }
        }
        return EXIT_FAILURE;
    }
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = *head;
        node *prev = NULL;
        unsigned int k = 0;
        while (cur != NULL) {
            if (k == pos) {
                if (prev != NULL) {
                    prev->next = cur->next;
                    return EXIT_SUCCESS;
                } else {
                    *head = cur->next;
                    return EXIT_SUCCESS;
                }
            } else {
                k++;
                prev = cur;
                cur = cur->next;
            }
        }
        return EXIT_FAILURE;
    }
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur1 = *head;
        node *cur2 = *head;
        unsigned int k1 = 0;
        unsigned int k2 = 0;
        while (cur1 != NULL) {
            if (k1 == pos1) {
                break;
            } else {
                k1++;
                cur1 = cur1->next;
            }
        }
        while (cur2 != NULL) {
            if (k2 == pos2) {
                break;
            } else {
                k2++;
                cur2 = cur2->next;
            }
        }
        if (cur1 == NULL || cur2 == NULL) {
            return EXIT_FAILURE;
        } else {
            cur1->item_name = malloc(strlen(cur2->item_name) + 1);
            if (cur1->item_name == NULL) {
                return EXIT_FAILURE;
            }
            strcpy(cur1->item_name, cur2->item_name);
            cur1->price = cur2->price;
            cur1->quantity = cur2->quantity;
            cur2->item_name = malloc(strlen(cur1->item_name) + 1);
            if (cur2->item_name == NULL) {
                return EXIT_FAILURE;
            }
            strcpy(cur2->item_name, cur1->item_name);
            cur2->price = cur1->price;
            cur2->quantity = cur1->quantity;
            return EXIT_SUCCESS;
        }
    }
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        int max = 0;
        node *cur = head;
        unsigned int k = 0;
        while (cur != NULL) {
            if (cur->price > max) {
                max = cur->price;
                *pos = k;
            }
            k++;
            cur = cur->next;
        }
        return EXIT_SUCCESS;
    }
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = head;
        *total = 0;
        while (cur != NULL) {
            *total += cur->price * cur->quantity;
            cur = cur->next;
        }
        return EXIT_SUCCESS;
    }
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        if (filename == NULL) {
            return EXIT_FAILURE;
        } else {
            FILE *f = fopen(filename, "w+");
            if (f == NULL) {
                return EXIT_FAILURE;
            } else {
                node *cur = head;
                while (cur != NULL) {
                    fprintf(f, "%s,%.2f,%d\n", cur->item_name, cur->price, cur->quantity);
                    cur = cur->next;
                }
                fclose(f);
                return EXIT_SUCCESS;
            }
        }
    }
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        if (filename == NULL) {
            return EXIT_FAILURE;
        } else {
            FILE *f = fopen(filename, "r");
            if (f == NULL) {
                return EXIT_FAILURE;
            } else {
                char *line = malloc(MAX_ITEM_PRINT_LEN);
                if (line == NULL) {
                    return EXIT_FAILURE;
                }
                while (fgets(line, MAX_ITEM_PRINT_LEN, f)) {
                    char *item_name = strtok(line, ",");
                    char *price = strtok(NULL, ",");
                    char *quantity = strtok(NULL, ",");
                    float f_price = atof(price);
                    int i_quantity = atoi(quantity);
                    list_add_item_at_pos(head, item_name, f_price, i_quantity, 0);
                }
                free(line);
                fclose(f);
                return EXIT_SUCCESS;
            }
        }
    }
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        int item_name_len = strlen((*head)->item_name);
        node *cur1 = *head;
        node *prev = NULL;
        node *cur2 = *head;
        while (cur1 != NULL) {
            while (cur2 != NULL) {
                if (cur1 != cur2 && strncmp(cur1->item_name, cur2->item_name, item_name_len) == 0) {
                    cur1->quantity += cur2->quantity;
                    cur2->quantity = 0;
                }
                cur2 = cur2->next;
            }
            cur1 = cur1->next;
            cur2 = *head;
        }
        return EXIT_SUCCESS;
    }
}
