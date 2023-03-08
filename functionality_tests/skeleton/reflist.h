#ifndef REFLIST_H
#define REFLIST_H

// This headerfile gives prototypes for the reference implementation
// of our linked list library.

int ref_list_init(node **head);

int ref_list_item_to_string(node *head, char *str);

int ref_list_print(node *head);

int ref_list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos);

int ref_list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos);

int ref_list_remove_item_at_pos(node **head, int pos);

int ref_list_swap_item_positions(node **head, int pos1, int pos2);

int ref_list_find_highest_price_item_position(node *head, int *pos);

int ref_list_cost_sum(node *head, float *total);

int ref_list_save(node *head, char *filename);

int ref_list_load(node **head, char *filename);

int ref_list_deduplicate(node **head);

#endif
