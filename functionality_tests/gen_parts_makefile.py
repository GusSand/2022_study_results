#!/usr/bin/env python

import os
import sys
import shlex
import json
import subprocess
from collections import defaultdict

CC = 'clang'
CFLAGS = shlex.split('-I. -Icmocka/include -g -Wall -Wno-unused-function -Wno-unused-variable')

expected_functions = [
    "list_init",
    "list_item_to_string",
    "list_print",
    "list_add_item_at_pos",
    "list_update_item_at_pos",
    "list_remove_item_at_pos",
    "list_swap_item_positions",
    "list_find_highest_price_item_position",
    "list_cost_sum",
    "list_save",
    "list_load",
    "list_deduplicate",
]

OBJS = ['reflist.o', 'cmocka/cmocka_nosig.o']

def build_dep_objs():
    for f in expected_functions:
        subprocess.check_call(['make', f'tests_ref/test_{f}.o'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    for o in OBJS:
        subprocess.check_call(['make', o], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

# Try to compile a source file with flags. Returns sys.maxsize if compilation failed,
# and the number of warnings otherwise.
def try_compile(func, source, flags, compiler=CC):
    res = subprocess.run([compiler, "-x", "c", "-o", source + '.o', "-c", source] + flags, check=False, stderr=subprocess.PIPE)
    if res.returncode != 0:
        # print(res.stderr.decode('utf-8'), file=sys.stderr)
        return sys.maxsize
    else:
        # Try to link the object file.
        ldres = subprocess.run(
            [compiler, '-o', '/dev/null', source + '.o'] + OBJS +  [f'tests_ref/test_{func}.o'],
            check=False, stderr=subprocess.PIPE
        )
        if ldres.returncode != 0:
            # print(ldres.stderr.decode('utf-8'), file=sys.stderr)
            return sys.maxsize
        else:
            return len(res.stderr.splitlines())

def paste_files(files, dest):
    with open(dest, 'w') as out:
        for f in files:
            with open(f) as inp:
                out.write(inp.read())

def files_identical(file1, file2):
    with open(file1) as f1, open(file2) as f2:
        return f1.read() == f2.read()

if len(sys.argv) != 2:
    print('Usage: gen_parts_makefile.py <src_dir>', file=sys.stderr)
    sys.exit(1)
srcdir = sys.argv[1]
os.chdir(srcdir)

report = json.load(open("parts/report.json"))

# Build dependencies
build_dep_objs()

api_report = {}

print()
for func in expected_functions:
    results = []
    if func not in report['functions']:
        report['functions'][func] = []
    for candidate in report['functions'][func]:
        if files_identical(candidate, f'unimp/{func}.c'):
            continue
        for prefix in [], ['parts/extra.c']:
            for extra_func in [[]] + [[f'parts/{e}.c'] for e in report['extra_functions']]:
                combo = ['parts/preamble.c'] + prefix + extra_func + [candidate]
                paste_files(combo, 'parts/test_combo.c')
                score = try_compile(func, 'parts/test_combo.c', CFLAGS)
                results.append((score, len(combo), combo))
    results.sort()
    if not results or results[0][0] == sys.maxsize:
        if not results:
            api_report[func] = 'unimplemented'
        elif results[0][0] == sys.maxsize:
            api_report[func] = 'compile_error'
        # We couldn't find a valid candidate. Use the stub implementation.
        combo = ['parts/preamble.c', f'unimp/{func}.c']
        paste_files(combo, 'parts/test_combo.c')
        assert try_compile(func, 'parts/test_combo.c', CFLAGS) == 0
        match = (0, len(combo), combo)
    else:
        api_report[func] = 'ok'
        match = results[0]
    # print(f"{func}: {match}")
    paste_files(match[2], f'parts/gen_{func}.c')
    os.remove('parts/test_combo.c')
    # Output the Makefile entry
    print(f"parts/gen_{func}.o: parts/gen_{func}.c")
    print(f"\t$(CC) -DUNIT_TESTING -c -o $@ $< $(CFLAGS)")

print()
for suite in ('tests_orig', 'tests_ref'):
    print(f"# ========= {suite} =========")
    suite_name = suite.split('_')[1]
    # Load mapping between test names and tested API function
    apis = defaultdict(list)
    tests = []
    for line in open(f"{suite}/all_tests.txt"):
        test, api = line.strip().split()
        apis[api].append(test)
        tests.append(f"{suite}/{test}.bin")
    for func in expected_functions:
        print(f"# tests for {func} in {suite}")
        for test in apis[func]:
            print(f"{suite}/{test}.bin: parts/gen_{func}.o reflist_testmode.o cmocka/cmocka_nosig.o {suite}/{test}.o")
            print(f"\t$(CC) -o $@ $^ $(CFLAGS)")
        print()
    print(f"{suite_name}_testsuite: {' '.join(tests)}")
    print()

with open(f'api_report.json', 'w') as out:
    json.dump(api_report, out, indent=2)
    out.write('\n')

c1, c2 = "API", "STATUS"
print(f"{c1:<40}   {c2}", file=sys.stderr)
for api in api_report:
    print(f"{api:<40s} : {api_report[api]}", file=sys.stderr)
