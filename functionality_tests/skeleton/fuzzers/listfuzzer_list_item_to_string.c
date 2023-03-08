#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "list.h"
#include "reflist.h"

int asan_detect_leaks = 1;

// Extra helper to free everything in the list
int list_free(node **head) {
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = *head;
    while (curr != NULL) {
        node *tmp = curr;
        curr = curr->next;
        free(tmp->item_name);
        free(tmp);
    }
    *head = NULL;
    return EXIT_SUCCESS;
}

// All ops that we will test here:
// 0 int ref_list_init(node **head);
// 1 int list_item_to_string(node *head, char *str);
// 2 int ref_list_print(node *head);
// 3 int ref_list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos);
// 4 int ref_list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos);
// 5 int ref_list_remove_item_at_pos(node **head, int pos);
// 6 int ref_list_swap_item_positions(node **head, int pos1, int pos2);
// 7 int ref_list_find_highest_price_item_position(node *head, int *pos);
// 8 int ref_list_cost_sum(node *head, float *total);
// 9 int ref_list_save(node *head, char *filename);
// 10 int ref_list_load(node **head, char *filename);
// 11 int ref_list_deduplicate(node **head);

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    node *head = NULL;
    float x;
    ref_list_init(&head);
    size_t i = 0;
    while (i < Size) {
        uint8_t op = Data[i++] % 12;
        // printf("i = %lu, op = %u\n", i, op);
        switch (op) {
            case 0:
                if (asan_detect_leaks) list_free(&head);
                ref_list_init(&head);
                break;
            case 1:
            {
                char str[100];
                list_item_to_string(head, str);
            }
                break;
            case 2:
                ref_list_print(head);
                break;
            case 3:
            {
                if (i + 1 >= Size) break;
                uint8_t pos = Data[i++];
                if (i + 1 >= Size) break;
                uint8_t len = Data[i++];
                if (i + len >= Size) break;
                char *item_name = malloc(len + 1);
                memcpy(item_name, Data + i, len);
                item_name[len] = '\0';
                i += len;
                if (i + sizeof(float) >= Size)  goto free_name_add;
                float price = *(float *) &Data[i];
                i += sizeof(float);
                if (i + sizeof(int) >= Size) goto free_name_add;
                int quantity = *(int *) &Data[i];
                i += sizeof(int);
                ref_list_add_item_at_pos(&head, item_name, price, quantity, pos);
free_name_add:
                if (asan_detect_leaks) free(item_name);
            }
                break;
            case 4:
            {
                if (i + 1 >= Size) break;
                uint8_t pos = Data[i++];
                if (i + 1 >= Size) break;
                uint8_t len = Data[i++];
                if (i + len >= Size) break;
                char *item_name = malloc(len + 1);
                memcpy(item_name, Data + i, len);
                item_name[len] = '\0';
                i += len;
                if (i + sizeof(float) >= Size) goto free_name_update;
                float price = *(float *) &Data[i];
                i += sizeof(float);
                if (i + sizeof(int) >= Size) goto free_name_update;
                int quantity = *(int *) &Data[i];
                i += sizeof(int);
                ref_list_update_item_at_pos(&head, item_name, price, quantity, pos);
free_name_update:
                if (asan_detect_leaks) free(item_name);
            }
                break;
            case 5:
            {
                if (i + 1 >= Size) break;
                uint8_t pos = Data[i++];
                ref_list_remove_item_at_pos(&head, pos);
            }
                break;
            case 6:
            {
                if (i + 1 >= Size) break;
                uint8_t pos1 = Data[i++];
                if (i + 1 >= Size) break;
                uint8_t pos2 = Data[i++];
                ref_list_swap_item_positions(&head, pos1, pos2);
            }
                break;
            case 7:
            {
                int pos;
                ref_list_find_highest_price_item_position(head, &pos);
            }
                break;
            case 8:
            {
                ref_list_cost_sum(head, &x);
            }
                break;
            case 9:
            {
                ref_list_save(head, "/tmp/listfuzzer.txt");
            }
                break;
            case 10:
            {
                if (i+128 >= Size) break;
                char filename[] = "/tmp/listfuzzer.XXXXXX";
                int fd = mkstemp(filename);
                if (fd == -1) break;
                write(fd, Data + i, 128);
                close(fd);
                ref_list_load(&head, filename);
                unlink(filename);
                i += 128;
            }
                break;
            case 11:
            {
                ref_list_deduplicate(&head);
            }
                break;
        }
    }
    if (asan_detect_leaks) list_free(&head);
    return 0;
}

int LLVMFuzzerInitialize(int *argc, char ***argv) {
    char *env = getenv("ASAN_OPTIONS");
    if (env && strstr(env, "detect_leaks=0") != NULL) {
        fprintf(stderr, "Note: leak check disabled so we will not try to free anything\n");
        asan_detect_leaks = 0;
    }
    return 0;
}
