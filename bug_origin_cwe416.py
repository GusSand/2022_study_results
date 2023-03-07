#!/usr/bin/env python

# This script generates a CSV file tracking the origin (document or suggestion) of the CWE-416 "strdup" bug.
# This corresponds to Table 5 in the paper.

import re
import pandas as pd
import json
from collections import namedtuple

Bug = namedtuple('Bug', ['CWE', 'CWE_Description', 'Description', 'Matcher', 'Normalizer'])

# In theory this could be extended to look for other kinds of bugs; we
# just need to define a Matcher and Normalizer for each bug. But right
# now only the CWE-416 strdup bug is implemented.
comment_re = re.compile(r'//.*')
def normalize(line):
    line = comment_re.sub('',line)
    return line

def bug_matches(bug, suggestion):
    return list(bug.Normalizer(line) for line in suggestion.splitlines() if bug.Matcher(bug.Normalizer(line)))

# CWE-416: Use After Free | Missing strdup (Potential Use After Free) (or similar)
item_name_assign = re.compile(r'(->|\.)\s*item_name.*=.*(->|\.)?\s*item_name')

def match_bug(line):
    return item_name_assign.search(line) and ('malloc' not in line) and ('strdup' not in line)

cwe416 = Bug('CWE-416', 'Use After Free', 'Missing strdup (Potential Use After Free) (or similar)', match_bug, normalize)

# Load the data
anubis = json.load(open('data/llm_log_dump.json'))
bug_data = pd.read_csv('data/bug_finding_flat.csv')

# Only care about Codex users
codex_data = bug_data[bug_data['Group'] == 'Codex']

# Find all users who had the strdup bug
missing_strdup = codex_data[codex_data['Description'] == cwe416.Description]

print('uuid,origin,num_bug_in_all_suggestions,num_bugs_in_taken_suggestions,bug_count_in_final_doc')
for uuid in sorted(list(set(missing_strdup['UUID']))):
    suggestions = anubis[uuid]['suggestions']
    documents = anubis[uuid]['documents']
    # Make a unified timeline of the suggestions and documents
    timeline = [ (s['timestamp'], 'Suggestion', s['suggestion'], s['taken']) for s in suggestions ] + \
               [ (d['timestamp'], 'Document', d['content'], None) for d in documents ]
    # Sort by timestamp
    timeline.sort(key=lambda x: x[0])
    # Iterate over the timeline, looking for the first time the bug was introduced
    for ts, event, text, taken in timeline:
        if event == 'Suggestion':
            takenstr = 'Taken' if taken else 'NotTaken'
        else:
            takenstr = 'N/A'
        if bug_matches(cwe416,text):
            num_bug_in_taken_suggestions = len([s for s in suggestions if bug_matches(cwe416,s['suggestion']) and s['taken']])
            num_bug_in_all_suggestions = len([s for s in suggestions if bug_matches(cwe416,s['suggestion'])])
            bug_count_in_final_doc = missing_strdup[missing_strdup['UUID'] == uuid]['Bug Count'].sum()
            print(f"{uuid[:4]},{event},{num_bug_in_all_suggestions},{num_bug_in_taken_suggestions},{bug_count_in_final_doc}")
            # Break since we only care about the first time the bug was introduced
            break
