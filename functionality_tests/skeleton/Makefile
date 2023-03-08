# CFLAGS=-I. -Icmocka/include -g
# We can enable colors here... but I don't know if it works on Windows
override CFLAGS += -I. -Icmocka/include -g -Wall -Wno-unused-function -Wno-unused-variable
DEPS = list.h
OBJ = list.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# cmocka without any signal handling
cmocka/cmocka_nosig.o: cmocka/cmocka.c
	$(CC) -DUNIT_TESTING_DEBUG -c -o $@ $< $(CFLAGS)

all: mylist runtests runtests_orig listfuzzer

mylist: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

list_testmode.o: list.c $(DEPS)
	$(CC) -DUNIT_TESTING -c -o $@ $< $(CFLAGS)

reflist_testmode.o: reflist.c $(DEPS)
	$(CC) -DUNIT_TESTING -c -o $@ $< $(CFLAGS)

runtests: list_testmode.o runtests.o cmocka/cmocka.o
	$(CC) -o $@ $^ $(CFLAGS)

runtests_orig: list_testmode.o runtests_orig.o cmocka/cmocka.o
	$(CC) -o $@ $^ $(CFLAGS)

listfuzzer: listfuzzer.c list.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)

.PHONY: coverage
coverage: CFLAGS += --coverage
coverage: clean check
	rm -rf coverage coverage.info
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '*/cmocka/*' --output-file coverage.info
	genhtml coverage.info --output-directory coverage

.PHONY: check
check: runtests
	timeout 1m ./runtests

.PHONY: check_orig
check_orig: runtests_orig
	timeout 1m ./runtests_orig

.PHONY: clean
clean:
	rm -f *.o cmocka/*.o runtests runtests_orig mylist listfuzzer *.gcda cmocka/*.gcda tests/*.gcda tests*/*.o tests*/*.bin

# Single-API fuzzers
fuzzers/listfuzzer_list_add_item_at_pos.bin: fuzzers/listfuzzer_list_add_item_at_pos.c reflist.c parts/gen_list_add_item_at_pos.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_cost_sum.bin: fuzzers/listfuzzer_list_cost_sum.c reflist.c parts/gen_list_cost_sum.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_deduplicate.bin: fuzzers/listfuzzer_list_deduplicate.c reflist.c parts/gen_list_deduplicate.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_find_highest_price_item_position.bin: fuzzers/listfuzzer_list_find_highest_price_item_position.c reflist.c parts/gen_list_find_highest_price_item_position.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_init.bin: fuzzers/listfuzzer_list_init.c reflist.c parts/gen_list_init.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_item_to_string.bin: fuzzers/listfuzzer_list_item_to_string.c reflist.c parts/gen_list_item_to_string.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_load.bin: fuzzers/listfuzzer_list_load.c reflist.c parts/gen_list_load.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_print.bin: fuzzers/listfuzzer_list_print.c reflist.c parts/gen_list_print.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_remove_item_at_pos.bin: fuzzers/listfuzzer_list_remove_item_at_pos.c reflist.c parts/gen_list_remove_item_at_pos.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_save.bin: fuzzers/listfuzzer_list_save.c reflist.c parts/gen_list_save.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_swap_item_positions.bin: fuzzers/listfuzzer_list_swap_item_positions.c reflist.c parts/gen_list_swap_item_positions.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers/listfuzzer_list_update_item_at_pos.bin: fuzzers/listfuzzer_list_update_item_at_pos.c reflist.c parts/gen_list_update_item_at_pos.c
	clang-14 -g -fsanitize=address,fuzzer -fsanitize-recover=address -o $@ $^ $(CFLAGS)
fuzzers: fuzzers/listfuzzer_list_add_item_at_pos.bin fuzzers/listfuzzer_list_cost_sum.bin fuzzers/listfuzzer_list_deduplicate.bin fuzzers/listfuzzer_list_find_highest_price_item_position.bin fuzzers/listfuzzer_list_init.bin fuzzers/listfuzzer_list_item_to_string.bin fuzzers/listfuzzer_list_load.bin fuzzers/listfuzzer_list_print.bin fuzzers/listfuzzer_list_remove_item_at_pos.bin fuzzers/listfuzzer_list_save.bin fuzzers/listfuzzer_list_swap_item_positions.bin fuzzers/listfuzzer_list_update_item_at_pos.bin
