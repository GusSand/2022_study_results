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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *current_item;
    current_item = head;
    int pos = 1;
    char* str;
    while (current_item != NULL) {
        printf("%d: ", pos);
        ref_list_item_to_string(current_item, str);
        printf(str);
        printf("\n");
        current_item = current_item->next;
        pos++;
    }
    return EXIT_SUCCESS;
}
