// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    strcpy(str, head->item_name);
    sprintf(str, "%s * %d @ $%.2f ea", head->item_name, head->quantity, head->price);
    return EXIT_SUCCESS;
}
