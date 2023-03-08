#!/usr/bin/env python

import sys
import re
import os
import json
from collections import defaultdict

DEBUG = False

def D(*args, **kwargs):
    if DEBUG: print(*args, **kwargs)

expected_functions = {
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
}

# Replace any calls to other API functions with a call to the reference implementation
def replace_with_ref(lines, api_func):
    out_lines = []
    for line in lines:
        for func in expected_functions - {api_func}:
            line = re.sub(r"\b" + func + r"\b", f"ref_{func}", line)
        out_lines.append(line)
    return out_lines

def func_sig_matches_expected(line):
    for x in expected_functions:
        if re.search("int +\\b" + x + "\\b", line):
            return x
    return None

def func_sig_matches(line):
    # Gnarly regex, but basically says: two or more words (possibly with *),
    # followed by a parenthesized string, followed by any number of non-colon characters.
    m = re.search(r"^([\w\*]+( )?){2,}\([^!@#$+%^]+?\)[^;]*$", line)
    if m:
        return m.group(1)
    return None

def extract_body(lines, protoline, only_expected=True):
    if only_expected:
        matcher = func_sig_matches_expected
    else:
        matcher = func_sig_matches
        
    D(f"Proto line: {lines[protoline].rstrip()}")
    # Seek backward to previous closing brace
    start = protoline - 1
    while start >= 0 and '}' not in lines[start] and lines[start] != '\n':
        start -= 1
    if start != 0: start += 1
    D(f"start: {start}")
    
    body = {}
    body['start'] = start

    # Let's look for the end
    end = protoline
    braces = 0
    # Seek forward to first opening brace
    while end < len(lines) and '{' not in lines[end]:
        D(f"Opening brace not found on line {end}")
        end += 1
    # We are now on a line with an opening brace
    D(f"Found opening brace on line {end}: {lines[end].rstrip()}")
    while end < len(lines):
        D(f"Checking line {end}: {lines[end].rstrip()}")

        # Sanity check here: if we've started another function then cut this off
        proto = matcher(lines[end])
        if proto and protoline != end:
            D(f"WARNING: next function ({proto}) started on line {end} before we finished reading this one ({func_name}) which started on line {protoline}")
            body['incomplete'] = True
            # Adjust end to be the line before the next function
            end -= 1
            break
        # We assume no one would be so depraved as to begin a function on the same
        # line as the closing brace for the previous function
        for j,c in enumerate(lines[end]):
            if c == '{':
                braces += 1
                D(f"[{end}:{j}] Open {{, {braces=}")
            elif c == '}':
                braces -= 1
                D(f"[{end}:{j}] Close }}, {braces=}")
        end += 1
        if braces == 0:
            body['incomplete'] = False
            break
    body['end'] = end
    return body

found_functions = set()
function_bodies = {}
dups = defaultdict(list)

lines = open(sys.argv[1]).readlines()
PREAMBLE_END_STRING = '// successful or not.\n'
PREAMBLE_ALT_STRING = '// to indicate whether the operation was successful or not.\n'
preamble_lines = []
for i,line in enumerate(lines):
    if line == PREAMBLE_END_STRING or line == PREAMBLE_ALT_STRING:
        preamble_lines = lines[:i]
        lines = lines[i+1:]
        break
else:
    print("No preamble found")
    sys.exit(1)

i = 0
while i < len(lines):
    x = func_sig_matches_expected(lines[i])
    if x:
        found_functions.add(x)

        # Make sure name is unique
        func_name = x
        func_version = 1
        while func_name in function_bodies:
            func_name = x + str(func_version)
            func_version += 1
        if func_name != x:
            dups[x].append(func_name)

        D(f"========> Getting body for {func_name}" + 
        (f" (renamed from {x})" if func_name != x else "") +
        "...")
        bodyinfo = extract_body(lines, i, only_expected=True)
        function_bodies[func_name] = bodyinfo

        D(f"{func_name} {bodyinfo['start']} {bodyinfo['end']}")
        
        i = bodyinfo['end']
    i += 1

fblist = []
for x in function_bodies:
    fblist.append((function_bodies[x]['start'], function_bodies[x]['end'], x, function_bodies[x]['incomplete']))
fblist.sort()

# Check for any overlaps
for i in range(len(fblist) - 1):
    start, end, name, incomplete = fblist[i]
    next_start, next_end, next_name, next_incomplete = fblist[i+1]
    if end > next_start:
        if incomplete:
            print(f"Fixing incomplete function {name}")
            function_bodies[name]['incomplete'] = False
            function_bodies[name]['end'] = next_start
        else:    
            print(f"ERROR: Overlap detected between {name} and {next_name}")
            print(f"{name} {start} {end}")
            print(f"{next_name} {next_start} {next_end}")
            sys.exit(1)

# Health checks
# Any required functions missing?
if found_functions != expected_functions:
    print("MISSING: " + ", ".join(expected_functions - found_functions))

# Print some coverage info
funcbody_lines = set()
for x in function_bodies:
    funcbody_lines.update(range(function_bodies[x]['start'], function_bodies[x]['end']))
print(f"First pass coverage info: {100*len(funcbody_lines)/len(lines):.2f}% ({len(funcbody_lines)}/{len(lines)}) of lines covered")
remaining_lines = []
for i in range(len(lines)):
    if i not in funcbody_lines:
        remaining_lines.append(lines[i])

extra_functions = set()
extra_bodies = {}
extra_dups = defaultdict(list)
# Second pass, find any functions that are not in the expected list
i = 0
while i < len(remaining_lines):
    x = func_sig_matches(remaining_lines[i])
    if x:
        extra_functions.add(x)

        # Make sure name is unique
        func_name = x
        func_version = 1
        while func_name in function_bodies:
            func_name = x + str(func_version)
            func_version += 1
        if func_name != x:
            extra_dups[x].append(func_name)

        D(f"========> Getting body for {func_name}" + 
        (f" (renamed from {x})" if func_name != x else "") +
        "...")
        bodyinfo = extract_body(remaining_lines, i, only_expected=False)
        extra_bodies[func_name] = bodyinfo

        D(f"{func_name} {bodyinfo['start']} {bodyinfo['end']}")
        
        i = bodyinfo['end']
    i += 1
extra_func_lines = set()
for x in extra_bodies:
    extra_func_lines.update(range(extra_bodies[x]['start'], extra_bodies[x]['end']))
print(f"Second pass coverage info: {100*len(extra_func_lines)/len(remaining_lines):.2f}% ({len(extra_func_lines)}/{len(remaining_lines)}) of lines covered")
blank_lines = 0
print(f"Uncovered lines:")
uncovered_lines = []
for i in range(len(remaining_lines)):
    if i not in extra_func_lines:
        if remaining_lines[i].strip() != "":
            print(f"{i:>3d}: {remaining_lines[i].rstrip()}")
        else:
            blank_lines += 1
        uncovered_lines.append(remaining_lines[i])
print(f"Total coverage info: {100*(len(funcbody_lines)+len(extra_func_lines)+blank_lines)/len(lines):.2f}% ({len(funcbody_lines)+len(extra_func_lines)+blank_lines}/{len(lines)}) of lines covered")

extra_fblist = []
for x in extra_bodies:
    extra_fblist.append((extra_bodies[x]['start'], extra_bodies[x]['end'], x, extra_bodies[x]['incomplete']))
extra_fblist.sort()

# Check for overlaps in the extra functions
for i in range(len(extra_fblist) - 1):
    start, end, name, incomplete = extra_fblist[i]
    next_start, next_end, next_name, next_incomplete = extra_fblist[i+1]
    if end > next_start:
        if incomplete:
            print(f"Fixing incomplete function {name}")
            extra_bodies[name]['incomplete'] = False
            extra_bodies[name]['end'] = next_start
        else:    
            print(f"ERROR: Overlap detected between {name} and {next_name}")
            print(f"{name} {start} {end}")
            print(f"{next_name} {next_start} {next_end}")
            sys.exit(1)

# Any functions duplicated?
for x in dups:
    print(f"DUPE {x},{','.join(dups[x])}")
for x in extra_dups:
    print(f"DUPE {x},{','.join(extra_dups[x])}")

print("Summary of required functions found:")
for start, end, name, incomplete in fblist:
    print(f"{name:40s} {start:>3d} {end:>3d} {incomplete}")
print("Summary of extra functions found:")
for start, end, name, incomplete in extra_fblist:
    print(f"{name:40s} {start:>3d} {end:>3d} {incomplete}")

uncovered_line_count = len(lines) - (len(funcbody_lines)+len(extra_func_lines)+blank_lines)
print(f"SUMMARY: {len(fblist)+len(extra_fblist)} functions found, {uncovered_line_count} uncovered lines")

outdir = os.path.join(os.path.dirname(sys.argv[1]), 'parts')
os.makedirs(outdir, exist_ok=True)
# Save the bodies out to individual files
with open(os.path.join(outdir, 'preamble.c'), 'w') as f:
    f.writelines(preamble_lines + [f'\n#include "reflist.h"\n'])
    print(f"Saved preamble to {f.name}")
for x in function_bodies:
    fname = os.path.join(outdir, x + ".c")
    with open(fname, "w") as f:
        start, end = function_bodies[x]['start'], function_bodies[x]['end']
        f.writelines(replace_with_ref(lines[start:end], x))
        print(f"Saved {x} to {fname}")
for x in extra_bodies:
    fname = os.path.join(outdir, x + ".c")
    with open(fname, "w") as f:
        start, end = extra_bodies[x]['start'], extra_bodies[x]['end']
        f.writelines(remaining_lines[start:end])
        print(f"Saved {x} to {fname}")
with open(os.path.join(outdir, 'extra.c'), 'w') as f:
    f.writelines(uncovered_lines)
    print(f"Saved any leftovers to {f.name}")

# Create json report
report = {
    'preamble': 'parts/preamble.c',
    'uncovered': 'parts/extra.c',
    'functions': {},
    'extra_functions': {},
    'dups': dups,
    'extra_dups': extra_dups,
}

done = set()
for x in dups:
    report['functions'][x] = [os.path.join('parts', x + '.c')] + [os.path.join('parts', y + '.c') for y in dups[x]]
    done.add(x)
    done.update(dups[x])
for x in extra_dups:
    report['extra_functions'][x] = [os.path.join('parts', x + '.c')] + [os.path.join('parts', y + '.c') for y in extra_dups[x]]
    done.add(x)
    done.update(extra_dups[x])
for x in function_bodies:
    if x not in done:
        report['functions'][x] = [os.path.join('parts', x + '.c')]
for x in extra_bodies:
    if x not in done:
        report['extra_functions'][x] = [os.path.join('parts', x + '.c')]

with open(os.path.join(outdir, 'report.json'), 'w') as f:
    json.dump(report, f, indent=2)
    f.write('\n')
    print(f"Saved report to {f.name}")
