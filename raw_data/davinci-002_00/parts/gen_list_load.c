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

#include "reflist.h"
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (read <= 3) {
            continue;
        }
        if (line[read-1] == '\n') {
            line[read-1] = '\0';
        }
        char *token = strtok(line, ",");
        char *item_name = malloc(strlen(token) + 1);
        strcpy(item_name, token);
        token = strtok(NULL, ",");
        float price = atof(token);
        token = strtok(NULL, ",");
        int quantity = atoi(token);
        if (*head == NULL) {
            *head = (node *)malloc(sizeof(node));
            (*head)->item_name = item_name;
            (*head)->price = price;
            (*head)->quantity = quantity;
            (*head)->next = NULL;
        } else {
            node *cur = *head;
            while (cur->next) {
                cur = cur->next;
            }
            cur->next = (node *)malloc(sizeof(node));
            cur->next->item_name = item_name;
            cur->next->price = price;
            cur->next->quantity = quantity;
            cur->next->next = NULL;
        }
    }
    fclose(fp);
    if (line) {
        free(line);
    }
    return EXIT_SUCCESS;
}
