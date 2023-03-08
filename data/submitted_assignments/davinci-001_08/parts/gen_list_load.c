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
    int result = EXIT_SUCCESS;
    node *current = NULL;
    node *next = NULL;
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        result = EXIT_FAILURE;
    } else {
        char buffer[128];
        while (fgets(buffer, 128, file)) {
            int pos = 0;
            int item_name_len = strlen(buffer);
            buffer[item_name_len - 1] = 0;

            while (buffer[pos] != ',') {
                pos++;
            }

            char *item_name = (char *)malloc(pos + 1);
            strncpy(item_name, buffer, pos);
            item_name[pos] = 0;
            float price = atof(buffer + pos + 1);
            int quantity = atoi(buffer + pos + 5);

            next = malloc(sizeof(node));
            next->item_name = item_name;
            next->price = price;
            next->quantity = quantity;
            next->next = NULL;

            if (current == NULL) {
                *head = next;
            } else {
                current->next = next;
            }

            current = next;
        }

        fclose(file);
    }

    return result;
}
