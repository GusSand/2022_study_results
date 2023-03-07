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
int CURR_LEN=0;

// Note: All list_ functions should return a status code
// EXIT_FAILURE or EXIT_SUCCESS to indicate whether the operation was 
// successful or not.

// create a new list
int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    char *item = head->c;
    float price = head->price;
    int quan = head->quantity;
    // char *s = quan +
    sprintf(str,"%d * %s @ %.2f ea",quan,item,price);
    printf("%d * %s @ %.2f ea",quan,item,price);
    // str = s;
    return EXIT_SUCCESS;
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    printf("Entered1");
    int pos = 0;
    struct _node *curr = head;
    printf("Entered2");
    while(curr){
        printf("Entered");
        char *s;
        list_item_to_string(curr,s);
        printf("%d: %s\n",pos,s);
        curr=curr->next;
        pos++;
    }
    return EXIT_SUCCESS;
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //pos=pos-1;
    // if(pos<1) return EXIT_FAILURE;
    // if(pos>CURR_LEN+1) return EXIT_FAILURE;
    printf("%s", item_name);
    CURR_LEN+=1;
    struct _node *nodeX = (struct _node*)malloc(sizeof (struct _node));
    nodeX->c = item_name; // *(nodeX).c
    nodeX->price = price;
    nodeX->quantity = quantity;
    // struct _node *head_c = *head;
    
    printf("\nCreated");
    if(pos==1)
    {
        printf("\n1");
        nodeX->next = *head;
        printf("\nChecked");
        *head = nodeX;
        printf("\nUpdated");
        printf("\n%s",(*head)->c);
    }
    // else{
        
    //     for(int i=1;i<pos-1;i++){
    //         head_c= head_c->next;
    //     }
    //     if(head_c->next!=NULL){
    //         nodeX->next = head_c->next;
    //     }
    //     else {
    //         nodeX->next = NULL;
    //     }
    //     // nodeX->next = head_c->next->next;
    //     head_c->next = nodeX;
    // }
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    struct _node *curr = *head;
    for(int i=1;i<pos;i++){
        curr=curr->next;
    }
    curr->c = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos>CURR_LEN) return EXIT_FAILURE;
    struct _node *curr = *head;
    for(int i=1;i<pos-1;i++){
        curr=curr->next;
    }
    curr->next = curr->next->next;
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos1>pos2){
        int x = pos1;
        pos1 = pos2;
        pos2 = x;
    }
    if(pos1<0||pos2>CURR_LEN) return EXIT_FAILURE;
    node *node1=NULL;
    node *node2=NULL;
    node *curr = *head;
    for(int i=0;i<pos2+1;i++){
        if(i==pos1){
            node1=curr;
        }
        else if (i==pos2)
        {
            char *x = node1->c;
            float y = node1->price;
            int z = node1->quantity;
            node1->c = node2->c;
            node1->price = node2->price;
            node1->quantity = node2->quantity;
            node2->c = x;
            node2->price = y;
            node2->quantity = z;
            break;
        }
        else{
            curr=curr->next;
        } 
        
    }
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    float highP = 0;
    node *curr = head;
    int currPos = 1;
    while(curr){
        if(highP<curr->price){
            *pos=currPos;
            highP = curr->price;
        } 
        currPos+1;
        curr=curr->next;
    }
    
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    float sum =0.0;
    node *curr = head;
    while(curr){
        sum = sum + (curr->price)*(curr->quantity);
        curr=curr->next;
    }
    *total = sum;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE *ftr;
    ftr = fopen("./saveFile.txt",'w');
    *filename = "saveFile.txt";
    node *curr = head;
    while(curr){
        fprintf(ftr,"%s,%f,%d\n",curr->c,curr->price,curr->quantity);
        curr=curr->next;
    }
    fclose(ftr);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE *ftr;
    char *line;
    char *token;
    node *curr = *head;
    while(curr->next){
        curr = curr->next;
    }
    ftr = fopen(*filename,'r');
    while(fgets(line,100,ftr)){
        struct _node *newNode = (struct _node*)malloc(sizeof (struct _node));
        token = strtok(line," ");
        int num =1;
        while(token){
            if(num==1){
                newNode->c = token;
                num+=1;
            }
            else if (num==2)
            {
                newNode->price = atof(token);
                num+=3;
            }
            else{
                newNode->quantity=atoi(token);
            }
        }
        num = 1;
        curr->next = newNode;
        curr = curr->next;
    }
    fclose(ftr);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    char *s[CURR_LEN];
    node *curr = *head;
    if(curr==NULL || curr->next==NULL) return EXIT_FAILURE;
    node *curr2 = *head;
    // curr = curr->next;
    int pointer =2;
    while(curr->next){
        int i=1;
        for(i=1;i<pointer;i++){
            if(strcmp(curr->next->c,curr2->c)==0){
                float updated_price=curr->next->price+curr2->price;
                int updated_q = curr->next->quantity+curr2->quantity;
                list_update_item_at_pos(head,curr2->c,updated_price,updated_q,i);
                list_remove_item_at_pos(head,pointer);
                break;
            }
            else {
                curr2=curr2->next;
            }
        }
        if(i==pointer){
            curr = curr->next;
        }
    }
    return EXIT_SUCCESS;

}

