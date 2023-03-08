#!/usr/bin/env python

import sys
import os
from count_lines_per_function import extract_all_bodies

api_funcs = [
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

# Recombine multiple list functions into a single file
script_dir = os.path.dirname(os.path.realpath(__file__))
repo_dir = sys.argv[1]
parts_dir = os.path.join(repo_dir, "parts")
preamble_file = os.path.join(script_dir, "auxdata", "preamble.c")

recombined = []

# Preamble
recombined += open(preamble_file).read().splitlines()
recombined += [""]

functions = {}

for func_name in api_funcs:
    func_file = os.path.join(parts_dir, f"gen_{func_name}.c")
    bodies = extract_all_bodies(func_file)
    for name, body in bodies.items():
        if name not in body:
            functions[name] = body

non_api_functions = set(functions.keys()) - set(api_funcs)
if non_api_functions:
    recombined += ['// Auxiliary functions\n\n']
    for func_name in non_api_functions:
        recombined += functions[func_name]['body']
        recombined += [""]

recombined += ['// Main API functions\n\n']
for func_name in api_funcs:
    recombined += functions[func_name]['body']
    recombined += [""]

print("\n".join(recombined))
