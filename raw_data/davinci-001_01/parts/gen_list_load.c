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
  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    return EXIT_FAILURE;
  }
  char *str = malloc(MAX_ITEM_PRINT_LEN * sizeof(char));
  while (fgets(str, MAX_ITEM_PRINT_LEN, fp)) {
    char *p_char = str;
    unsigned int i = 0;
    node *temp = *head;
    while (*p_char != ',') {
      p_char++;
      i++;
    }
    *p_char = '\0';
    p_char++;
    char *p_char2 = p_char;
    while (*p_char2 != ',') {
      p_char2++;
      i++;
    }
    *p_char2 = '\0';
    p_char2++;
    float price = atof(p_char);
    int quantity = atoi(p_char2);
    ref_list_add_item_at_pos(head, str, price, quantity, i);
  }
  free(str);
  fclose(fp);
  return EXIT_SUCCESS;
}
