#!/bin/bash

cd "$1"
make clean ; make runtests &> build.log

# Split up the code into parts and create the Makefile
make clean
python ../../split_list_file.py list.c 
python ../../gen_parts_makefile.py . >> Makefile

echo "Running new test suite"
# per-API test suite
make clean ; make ref_testsuite &> build_ref_testsuite.log
python ../../run_testsuite.py tests_ref > ref_testsuite.json
make clean ; make ref_testsuite CFLAGS=-fsanitize=address &> build_ref_testsuite_asan.log
python ../../run_testsuite.py tests_ref > ref_testsuite_asan.json
ASAN_OPTIONS=detect_leaks=0 python ../../run_testsuite.py tests_ref > ref_testsuite_asan_noleak.json

echo "Running original test suite"
# per-API original test suite
make clean ; make orig_testsuite &> build_orig_testsuite.log
python ../../run_testsuite.py tests_orig > orig_testsuite.json
make clean ; make orig_testsuite CFLAGS=-fsanitize=address &> build_orig_testsuite_asan.log
python ../../run_testsuite.py tests_orig > orig_testsuite_asan.json
ASAN_OPTIONS=detect_leaks=0 python ../../run_testsuite.py tests_orig > orig_testsuite_asan_noleak.json

echo "Not performing fuzzing. If you would like to run the fuzzers, edit grade.sh comment out line 29"
exit

# One hour
FUZZER_TIME=3600

# Fuzzers
make clean fuzzers &> /dev/null
for run in {1..10}; do
    for fuzzer in fuzzers/*.bin ; do
        name=$(basename ${fuzzer/.bin/})
        echo "$name"
        mkdir ${name}_outputs_${run} ${name}_outputs_noleak_${run}
        mkdir ${name}_crashes_${run} ${name}_crashes_noleak_${run}
        start_time=$(date +%s)
        elapsed=0
        while [[ $elapsed -lt $FUZZER_TIME ]]; do
        ASAN_OPTIONS="detect_leaks=1:halt_on_error=0" timeout -k 30s 5m ${fuzzer} -print_coverage=1 -print_final_stats=1 -artifact_prefix=${name}_crashes_${run}/ -max_total_time=300 -timeout=2 -close_fd_mask=1 ${name}_outputs_${run} &>> ${name}_${run}.log
        elapsed=$(( $(date +%s) - start_time ))
        done
        start_time=$(date +%s)
        elapsed=0
        while [[ $elapsed -lt $FUZZER_TIME ]]; do
        ASAN_OPTIONS="detect_leaks=0:halt_on_error=0" timeout -k 30s 5m ${fuzzer} -print_coverage=1 -print_final_stats=1 -artifact_prefix=${name}_crashes_noleak_${run}/ -max_total_time=300 -timeout=2 -close_fd_mask=1 ${name}_outputs_noleak_${run} &>> ${name}_noleak_${run}.log
        elapsed=$(( $(date +%s) - start_time ))
        done
    done
done
