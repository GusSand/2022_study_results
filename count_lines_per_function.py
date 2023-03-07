#!/usr/bin/env python

import json
import re
import os

DEBUG = bool(os.environ.get('DEBUG', False))

def D(*args, **kwargs):
    if DEBUG: print(*args, **kwargs)

def func_sig_matches(line):
    m = re.search(r"^([\w\*]+)( [\w\*]+)+ *\([^;]*$", line)
    if m:
        return m.groups()[-1].strip()
    return None

def extract_body(lines, protoline, func_name):
    matcher = func_sig_matches

    D(f"Proto line: {lines[protoline].rstrip()}")
    start = protoline
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

def extract_all_bodies(file_name):
    return extract_all_bodies_from_str(open(file_name).read())

def extract_all_bodies_from_str(s):
    bodies = {}
    lines = s.split('\n')
    i = 0
    while i < len(lines):
        func_name = func_sig_matches(lines[i])
        if func_name:
            # Make sure name is unique
            func_name_temp = func_name
            func_version = 1
            while func_name in bodies:
                func_name = func_name_temp + str(func_version)
                func_version += 1
            if func_name != func_name_temp:
                D(f"Renamed duplicate function {func_name_temp} to {func_name}")
            func_name = func_name.strip()
            D(f"Found function {func_name} on line {i}: {lines[i].rstrip()}")
            D(f"========> Getting body for {func_name}...")
            bodyinfo = extract_body(lines, i, func_name)
            assert func_name not in bodies
            bodies[func_name] = bodyinfo

            D(f"{func_name} {bodyinfo['start']} {bodyinfo['end']}")

            i = bodyinfo['end']
        i += 1
    # Add bodies
    for bodyinfo in bodies.values():
        bodyinfo['body'] = lines[bodyinfo['start']:bodyinfo['end']]
    return bodies

# Count the number of non-empty, non-comment lines in a file.
def count_lines(file_name):
    bodies = extract_all_bodies(file_name)
    # Strip empty and comment lines in the bodies
    for func_name, bodyinfo in bodies.items():
        body = bodyinfo['body']
        body = [line for line in body if line.strip() and not line.strip().startswith('//')]
        D(f"{func_name} {len(body)}")
        D("".join(f"{i:2d} {l}" for i,l in enumerate(body)))
        for line in body:
            assert "/*" not in line
        bodies[func_name] = len(body)
    return sum(bodies.values()), list(bodies.keys())

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <file> [<file> ...]")
        sys.exit(1)
    for file_name in sys.argv[1:]:
        for line in open(file_name):
            if func := func_sig_matches(line):
                print(f"{file_name}: {func}")
    sys.exit(0)
