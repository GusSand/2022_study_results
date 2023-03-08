// Return a pointer to the item in the list at position pos.
// Note: This 
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
    node *current_item;
    current_item = *head;
    node *new_item = malloc(sizeof(node));
    strcpy(new_item->item_name, item_name);
    new_item->price = price;
    new_item->quantity = quantity;
    new_item->next = NULL;
    if (pos == 0) {
        new_item->next = *head;
        *head = new_item;
        return EXIT_SUCCESS;
    }
    for (int i = 1; i < pos; i++) {
        if (current_item->next == NULL) {
            printf("Cannot add item at position %d", pos);
            return EXIT_FAILURE;
        }
        current_item = current_item->next;
    }
    new_item->next = current_item->next;
    current_item->next = new_item;
    return EXIT_SUCCESS;
}
