// No unistd.h on clang for Windows?
#ifndef _WIN32
#include <unistd.h>
#endif

#include <string.h>
#include <stdint.h>
#include <signal.h>
#include "list.h"
#include "reflist.h"
#include "cmocka.h"

// Content for the test cases
static char badfile[] = "apple,0.80,2\n"
                        "wharblgarble\n";
static char goodfile[] = "apple,0.80,2\n"
                         "banana,0.50,3\n"
                         "cheese,10.59,1\n";
static char longfile[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa,1.0,1\n";

#ifdef _WIN32
// Compatibility with the Windows standard C library.
#define vsnprintf _vsnprintf
#endif /* _WIN32 */

// Extra helper to free everything in the list
static int list_free(node **head) {
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = *head;
    while (curr != NULL) {
        node *tmp = curr;
        curr = curr->next;
        if (tmp->item_name) free(tmp->item_name);
        if (tmp) free(tmp);
    }
    *head = NULL;
    return EXIT_SUCCESS;
}

static char big_buffer[1024];

int test_printf(const char *format, ...) CMOCKA_PRINTF_ATTRIBUTE(1, 2);

// A mock printf function that just gathers up the strings printed
// into a big buffer so that they can be checked later.
int test_printf(const char *format, ...) {
	int return_value;
    char temporary_buffer[256];
	va_list args;
	va_start(args, format);
	return_value = vsnprintf(temporary_buffer, sizeof(temporary_buffer),
	                         format, args);
    function_called();
    // Concatenate the temporary buffer to the big buffer.
    strcat(big_buffer, temporary_buffer);
	va_end(args);
	return return_value;
}

static int getTempFilename(void **state) {
    char *filename = strdup("test.XXXXXX");
    mktemp(filename);
    *state = filename;
    return 0;
}

static int removeTempFile(void **state) {
    char *filename = *state;
    // We don't care if it fails
    remove(filename);
    free(filename);
    return 0;
}

// Helper for test_list_load
static void create_file_with_content(const char *filename, const char *content, size_t size) {
    FILE *fp = fopen(filename, "w");
    assert_non_null(fp);
    // We use size - 1 to avoid writing a trailing NULL
    assert_int_equal(fwrite(content, 1, size-1, fp), size-1);
    assert_int_equal(fclose(fp), 0);
}
