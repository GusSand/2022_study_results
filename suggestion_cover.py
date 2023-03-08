#!/usr/bin/env python

import editdistance
import json
import os
import sys
import html
import difflib
import dateutil
import dateutil.parser
from count_lines_per_function import extract_all_bodies_from_str, func_sig_matches
import argparse

def load_active_inactive(active_inactive_txt):
    with open(active_inactive_txt) as fd:
        return {line.split()[0]: line.strip().split()[1] for line in fd.readlines()}

DEBUG = bool(os.environ.get('DEBUG', False))

def D(*args, **kwargs):
    if DEBUG: print(*args, **kwargs, file=sys.stderr)

EDIT_DISTANCE_THRESHOLD = 0.50

parser = argparse.ArgumentParser(description="Generate an HTML document showing the closest-matching suggestions for the Codex user study")
parser.add_argument("-o", "--output", default=None, help="output file to write to")
parser.add_argument("-f", "--function-level", action='store_true', help="only consider suggestions where the cursor is in the current function")
parser.add_argument("-e", "--edit-distance", type=float, default=EDIT_DISTANCE_THRESHOLD, help="threshold for consider an approximate match")
args = parser.parse_args()

if args.output is None:
    output_file = sys.stdout
    json_out = open('data/derived_data/suggestion_cover.jsonl', 'w')
else:
    output_file = open(args.output, 'w')
    json_out = open(args.output.replace(".html",".jsonl"),'w')

EDIT_DISTANCE_THRESHOLD = args.edit_distance

# Strings that help identify different documents since we don't
# have the file name.
README_STR = '# Programming assignment'
LIST_C_START = '#include <stdio.h>'
RUNTEST_STR = '#include <setjmp.h>'
LIST_H_STR = '#ifndef LIST_H'
MAIN_C_STR = '#define MAX_FILENAME_LEN 100'

def parse_timestamp(timestamp):
    # Parse a timestamp like 2022-04-21T17:09:26.353Z
    ts = dateutil.parser.parse(timestamp)
    # Convert to US/Eastern time
    ts = ts.astimezone(dateutil.tz.gettz('US/Eastern'))
    return ts

CSS_AND_JS = """
<style>
body {
    background-color: rgb(41, 44, 51);
    font-family: sans-serif;
    color: rgb(200, 200, 200);
}
h1, h2, h3, h4 {
    margin: 0;
}
.human {
    color: lightblue;
    display: inline;
}
.template {
    color: darkgrey;
}
.missing {
    color: red;
}
.codex {
    color: green;
}
.codex-approximate {
    color: orange;
}
.codex-alternate {
    display: none;
    position: absolute;
    color: lightgrey;
    background: rgba(41, 44, 51,0.9);
    border: 2px solid red;
}
.codex-alternate > center {
    font-family: sans-serif;
    font-weight: bold;
    color: black;
    background-color: rgba(200, 200, 200, 0.9);
}
code div {
    display: inline;
}
.suggestionlines {
    display: inline;
    margin: 0;
    padding: 0;
}
pre {
    white-space: pre-wrap;
}
pre:before {
  counter-reset: listing;
}
pre code {
  counter-increment: listing;
}
pre code:before {
  content: counter(listing) " ";
  display: inline-block;
  width: 2.5em;
  margin-left: auto;
  text-align: right;
  border-right: 1px solid #ccc;
  padding: 0 .5em;
  margin-right: .5em;
}
</style>
<script>
function showbox(e) {
    // Get the descendant with class 'codex-alternate'
    var children = e.getElementsByTagName('*');
    var alternate = null;
    for(const d of children){
        if (d.className == 'codex-alternate') {
            alternate = d;
            break;
        }
    }
    // Show the alternate, starting at the width of e
    alternate.style.display = "block";
    const domRect = e.getBoundingClientRect()
    alternate.style.left = (domRect.x + domRect.width + 5) + "px";
    alternate.style.top = (e.offsetTop - 2) + "px";
}
function hidebox(e) {
    // Get the descendant with class 'codex-alternate'
    var children = e.getElementsByTagName('*');
    var alternate = null;
    for(const d of children){
        if (d.className == 'codex-alternate') {
            alternate = d;
            break;
        }
    }
    alternate.style.display = "none";
}
</script>
"""

def suggestion_char_diff_html(real, suggestion):
    differ = difflib.Differ()
    diff = differ.compare(real, suggestion)
    matched = 0
    outchars = ''
    for line in diff:
        if line.startswith('+'):
            outchars += '<span class="missing">' + html.escape(line[2:]) + '</span>'
            matched += 1
        elif line.startswith('-') or line.startswith('?'):
            continue
        else:
            outchars += html.escape(line[2:])
            matched += 1
    assert matched == len(suggestion)
    return outchars

def make_lines(document_parts):
    lines = []
    need_rest_of_line = False
    for label, text, _, extra_info in document_parts:
        if extra_info: extra_info['orig_text'] = text
        for line in text.splitlines():
            if need_rest_of_line:
                lines[-1].append((label, line, extra_info))
                need_rest_of_line = False
            else:
                lines.append([(label, line, extra_info)])
        if not text.endswith('\n'):
            need_rest_of_line = True
    # Add newlines back in
    for parts in lines:
        if not parts[-1][1].endswith('\n'):
            parts[-1] = (parts[-1][0], parts[-1][1] + '\n', parts[-1][2])
    # Go through lines; for each run of lines that has a Codex suggestion,
    # insert a marker before the first line of the run and after the last line.
    # This will allow us to highlight the entire run of lines.
    def has_codex_part(parts):
        for label, _, _ in parts:
            if label.startswith('Codex'):
                return True
        return False
    def codex_info(parts):
        for label, _, extra_info in parts:
            if label.startswith('Codex'):
                return extra_info
        return None
    i = 0
    in_suggestion = False
    while i < len(lines) - 1:
        this_line = lines[i]
        next_line = lines[i+1]
        if not has_codex_part(this_line) and has_codex_part(next_line):
            lines.insert(i+1, [('SuggestionGroupStart', '', {})])
            in_suggestion = True
            i += 1
        if has_codex_part(this_line) and not has_codex_part(next_line):
            lines.insert(i+1, [('SuggestionGroupEnd', '', {})])
            in_suggestion = False
            i += 1
        if has_codex_part(this_line) and has_codex_part(next_line):
            # Compare extra_info for the two lines. If they're different,
            # insert a SuggestionGroupEnd before the next line.
            this_extra_info = codex_info(this_line)
            next_extra_info = codex_info(next_line)
            if this_extra_info != next_extra_info:
                lines.insert(i+1, [('SuggestionGroupEnd', '', {})])
                lines.insert(i+2, [('SuggestionGroupStart', '', {})])
                i += 2
        i += 1
    if in_suggestion:
        lines.append([('SuggestionGroupEnd', '', {})])
    return lines

def print_document_html(uuid, document_parts, matchdata, file=output_file):
    num_taken_suggestions_matched = matchdata['matched']
    num_taken_suggestions_matched_approx = matchdata['matched_approx']
    num_taken_suggestions = matchdata['total']
    # Print the document parts, colored by label.
    print("<hr>", file=file)
    missing_suggestions = num_taken_suggestions-(num_taken_suggestions_matched+num_taken_suggestions_matched_approx)
    suggestion_stats = (f"Out of {num_taken_suggestions} taken suggestions: "
                        f"<span class='codex'>{num_taken_suggestions_matched} match</span>, "
                        f"<span class='codex-approximate'>{num_taken_suggestions_matched_approx} approx</span>, "
                        f"<span class='missing'>{missing_suggestions} missing</span>")
    matched_template = sum(len(p[1]) for p in document_parts if p[0] == 'Template')
    matched_exact = sum(len(p[1]) for p in document_parts if p[0] == 'Codex')
    matched_approx = sum(len(p[1]) for p in document_parts if p[0] == 'CodexApproximate')
    matched_human = sum(len(p[1]) for p in document_parts if p[0] == 'Human')
    total = sum(len(p[1]) for p in document_parts)
    coverage_stats = (f"<span class='template'>{int(100*matched_template/total)}% template</span>, "
                      f"<span class='codex'>{int(100*matched_exact/total)}% exact</span>, "
                      f"<span class='codex-approximate'>{int(100*matched_approx/total)}% approx</span>, "
                      f"<span class='human'>{int(100*matched_human/total)}% human</span>")
    coverage_summary = f"Codex wrote ~{100*(matched_exact+matched_approx)/total:.2f}% of the document"
    print(f"<h3>User: {uuid}</h3><h4><br>{suggestion_stats}<br>Coverage: {coverage_stats}<br>{coverage_summary}</h4>", file=file)

    print("<pre>", file=file)
    lines = make_lines(document_parts)

    for line in lines:
        if line[0][0] == 'SuggestionGroupStart':
            print("<div class='suggestionlines' onmouseover='showbox(this)' onmouseout='hidebox(this)'>", end='', file=file)
            continue
        elif line[0][0] == 'SuggestionGroupEnd':
            print("</div>", end='', file=file)
            continue
        # Not a marker line, process as usual
        print("<code>", file=file, end="")
        for label, text, extra_info in line:
            etext = html.escape(text)
            if label == 'Human':
                print(f"<div class='human' title='Human-written'>{etext}</div>", end='', file=file)
            elif label == 'Codex':
                ts = parse_timestamp(extra_info['ts']).strftime('%Y-%m-%d %H:%M:%S')
                suggestion = extra_info['text']
                if suggestion[0] == '\n': suggestion = suggestion[1:]
                suggestion = html.escape(suggestion)
                suggestion_div = f"<div class='codex-alternate'>{suggestion}<br><center>[Suggestion {ts}] (exact match)</center></div>"
                print(f"<div class='codex'>{etext}</div>{suggestion_div}", end='', file=file)
            elif label == 'CodexApproximate':
                suggestion = extra_info['text']
                ts = parse_timestamp(extra_info['ts']).strftime('%Y-%m-%d %H:%M:%S')
                distance = extra_info['distance']
                suggestion = suggestion_char_diff_html(extra_info['orig_text'], suggestion)
                suggestion_div = f"<div class='codex-alternate'>{suggestion}<br><center>[Suggestion {ts}] (distance: {distance:.2f})</center></div>"
                print(f"<div class='codex-approximate'>{etext}</div>{suggestion_div}", end='', file=file)
            elif label == 'Template':
                print(f"<div class='template' title='Unmodified list.c'>{etext}</div>", end='', file=file)
            elif label == 'SuggestionGroupStart' or label == 'SuggestionGroupEnd':
                pass
            else:
                print(f"<div class='unknown'>{etext}</div>", end='', file=file)
        print("</code>", end='', file=file)
    print("</pre>", file=file)
    print(file=file)

def print_html_header(file=output_file):
    print("<html><head>", file=file)
    print(CSS_AND_JS, file=file)
    print("</head><body>", file=file)
    print("<h1>Suggestion Coverage</h1>", file=file)
    print(f"<h3>Legend: ", file=file)
    print(f"<span class='template'>[ Template list.c ]</span> ", file=file)
    print(f"<span class='human'>[ Human-written ]</span> ", file=file)
    print(f"<span class='codex'>[ Codex ]</span>", file=file)
    print(f"<span class='codex-approximate'>[ Codex (approximate match) ]</span>", file=file)
    print(f"</h3>", file=file)
    print(f"<h3>Edit distance threshold: {100*EDIT_DISTANCE_THRESHOLD:.0f}%</h3>", file=file)

def print_html_footer(matchdata, file=output_file):
    matched_template = matchdata['matched_template']
    matched_exact = matchdata['matched_exact']
    matched_approx = matchdata['matched_approx']
    matched_human = matchdata['matched_human']
    total = matchdata['total']
    num_taken_suggestions_matched = matchdata['suggestions_matched']
    num_taken_suggestions_matched_approx = matchdata['suggestions_approx']
    num_taken_suggestions = matchdata['suggestions_total']
    missing_suggestions = num_taken_suggestions-(num_taken_suggestions_matched+num_taken_suggestions_matched_approx)
    suggestion_stats = (f"Out of {num_taken_suggestions} taken suggestions: "
                        f"<span class='codex'>{num_taken_suggestions_matched} match</span>, "
                        f"<span class='codex-approximate'>{num_taken_suggestions_matched_approx} approx</span>, "
                        f"<span class='missing'>{missing_suggestions} missing</span>")

    coverage_stats = (f"<span class='template'>{int(100*matched_template/total)}% template</span>, "
                      f"<span class='codex'>{int(100*matched_exact/total)}% exact</span>, "
                      f"<span class='codex-approximate'>{int(100*matched_approx/total)}% approx</span>, "
                      f"<span class='human'>{int(100*matched_human/total)}% human</span>")
    coverage_summary = f"Codex wrote ~{100*(matched_exact+matched_approx)/total:.2f}% of all documents"
    print("<hr>", file=file)
    print(f"<h3>Across all Assisted users:</h3><h4><br>{suggestion_stats}<br>Coverage: {coverage_stats}<br>{coverage_summary}</h4>", file=file)
    print("</body></html>", file=file)

def print_text_summary(matchdata, file=output_file):
    matched_template = matchdata['matched_template']
    matched_exact = matchdata['matched_exact']
    matched_approx = matchdata['matched_approx']
    matched_human = matchdata['matched_human']
    total = matchdata['total']

    coverage_stats = (f"{int(100*matched_template/total):2}% Template\n"
                      f"{int(100*matched_human/total):2}% Human\n"
                      f"{int(100*matched_exact/total):2}% Codex (exact)\n"
                      f"{int(100*matched_approx/total):2}% Codex (approx)")
    total_no_template = total - matched_template
    coverage_stats_no_template = (f"{int(100*matched_human/total_no_template):2}% Human\n"
                                  f"{int(100*matched_exact/total_no_template):2}% Codex (exact)\n"
                                  f"{int(100*matched_approx/total_no_template):2}% Codex (approx)")
    print("\nSummary:\n", file=file)
    print("Coverage including template lines:", file=file)
    print(coverage_stats, file=file)
    print(file=file)
    print("Coverage excluding template lines:", file=file)
    print(coverage_stats_no_template, file=file)

# Eaxct match
def match_exact(part, candidate):
    if len(candidate) > len(part): return None
    matchidx = part.rfind(candidate)
    if matchidx == -1: return None
    return part[:matchidx], candidate, part[matchidx+len(candidate):], 0

# Approximate match using normalized edit distance
def match_approximate(part, candidate):
    # print(f"In match_approximate")
    candidate_len = len(candidate)
    if candidate_len > len(part): return None
    # print(f"{candidate_len=} <= {len(part)=}")
    # For each candidate_len-sized substring of part, check edit distance
    distances = []
    for i in range(len(part)-candidate_len+1):
        subpart = part[i:i+candidate_len]
        normalized_dist = editdistance.eval(subpart, candidate) / candidate_len
        # print(f"{normalized_dist:.3f} {repr(subpart)} {repr(candidate)}")
        if normalized_dist < EDIT_DISTANCE_THRESHOLD:
            distances.append((normalized_dist, i, subpart))
    if not distances: return None
    # Get the closest match
    min_dist, i, closest = min(distances, key=lambda x: x[0])
    return part[:i], part[i:i+len(candidate)], part[i+len(candidate):], min_dist

# Match greedily character by character
def match_lines_difflib(template, candidate):
    differ = difflib.Differ()
    match_groups = []
    matched = []
    unmatched = []
    for m in differ.compare(template.splitlines(), candidate.splitlines()):
        if m.startswith(' '):
            matched.append(m[2:])
            if unmatched:
                match_groups.append(('Human', unmatched))
                unmatched = []
        elif m.startswith('+'):
            unmatched.append(m[2:])
            if matched:
                match_groups.append(('Template', matched))
                matched = []
        elif m.startswith('-') or m.startswith('?'):
            continue
        else:
            raise ValueError(f"Unknown match type {m[0]}")
    if matched:
        match_groups.append(('Template', matched))
    if unmatched:
        match_groups.append(('Human', unmatched))
    assert not (matched and unmatched)
    # Add the newlines back in and join each group
    return [(label, ''.join(l+"\n" for l in group), None) for label, group in match_groups]

anubis = json.load(open('data/llm_log_dump.json'))
active_inactive = load_active_inactive('data/active_inactive.txt')
codex_users = [uuid for uuid in active_inactive if active_inactive[uuid] == 'Active' and uuid in anubis]

print_html_header()

combined_matchdata = {
    'matched_template': 0,
    'matched_exact': 0,
    'matched_approx': 0,
    'matched_human': 0,
    'total': 0,
    'suggestions_matched': 0,
    'suggestions_approx': 0,
    'suggestions_total': 0,
}

# Given a list of parts
#  (label, text, None)
# where label is either 'Template' or 'Human', fill in the third element with
# the function name for that part (may need to split it into multiple parts).
def annotate_parts_by_function(parts):
    doc = ''.join(part for _, part, _ in parts)
    lines = doc.splitlines()
    bodies = extract_all_bodies_from_str(doc)
    bodies_sorted = []
    for func in sorted(bodies, key=lambda x: bodies[x]['start']):
        bodies_sorted.append((func,bodies[func]))
    start_char = 0
    current_char = 0
    current_function = None
    ranges = []
    for i, line in enumerate(lines):
        if bodies_sorted and i == bodies_sorted[0][1]['start']:
            ranges.append((start_char, current_char, current_function))
            current_function = bodies_sorted[0][0]
            start_char = current_char
        elif bodies_sorted and i == bodies_sorted[0][1]['end']:
            ranges.append((start_char, current_char, current_function))
            current_function = None
            start_char = current_char
            bodies_sorted = bodies_sorted[1:]
        current_char += len(line)+1
    ranges.append((start_char, current_char, current_function))

    rangemap = {}
    for i, (start, end, func) in enumerate(ranges):
        for j in range(start, end):
            rangemap[j] = func

    new_parts = []
    part_start = 0
    part_end = 0
    current_label = None
    current_text = ""
    current_func = None
    for part_label, text, _ in parts:
        D(f"Annotating {part_label} {repr(text)}")
        current_label = part_label
        part_end = part_start + len(text)
        for i in range(part_start, part_end):
            # Which range are we in?
            func = rangemap[i]
            D(f"{i=} {current_label} {func=}", file=sys.stderr)
            if func != current_func:
                if current_text:
                    D(f"Adding {current_label=} {current_func=} {repr(current_text)}")
                    new_parts.append((current_label, current_text, current_func))
                current_text = ""
                current_func = func
            current_text += text[i-part_start]
        if current_text:
            D(f"Adding {current_label=} {current_func=} {repr(current_text)}")
            new_parts.append((current_label, current_text, current_func))
        current_text = ""
        part_start = part_end
    if current_text:
        D(f"Adding {current_label=} {current_func=} {repr(current_text)}")
        new_parts.append((current_label, current_text, current_func))
    return new_parts

def get_suggestion_cursor_func(suggestion):
    lines = suggestion['input'].splitlines()
    for line in reversed(lines):
        if func := func_sig_matches(line):
            return func
    return None

for uuid in codex_users:
    print(f"Processing {uuid}...", file=sys.stderr)
    # Get the unmodified list.c
    unmodified_document = open(os.path.join('data', 'submitted_assignments', 'unmodified', 'list.c')).read()
    # Get their final list.c
    document_file = os.path.join('data', 'submitted_assignments', uuid, 'list.c')
    if not os.path.exists(document_file): continue
    final_document = open(document_file).read()
    # If it doesn't end with a newline, add one for consistency
    if final_document[-1] != '\n':
        final_document += '\n'

    # Document will have (label, text, None) (None will be filled in with the
    # function name later). Labels are Template, Human, Codex, and CodexApproximate.
    document_parts = match_lines_difflib(unmodified_document, final_document)

    D("Before annotation:")
    D(json.dumps(document_parts, indent=2))
    document_parts = annotate_parts_by_function(document_parts)
    D("After annotation:")
    D(json.dumps(document_parts, indent=2))
    assert ''.join(part[1] for part in document_parts) == final_document

    # Add field for extra_info
    document_parts = [ (tuple(list(part) + [None])) for part in document_parts ]

    # Filter out suggestions that aren't relevant to us
    suggestions = [s for s in anubis[uuid]['suggestions']
                    if len(s['suggestion']) > 0 and
                        s['language'] == 'c' and
                        RUNTEST_STR not in s['input'] and
                        LIST_H_STR not in s['input'] and
                        MAIN_C_STR not in s['input'] and
                        s['taken']]
    if not suggestions: continue
    num_taken_suggestions = len(suggestions)
    num_taken_suggestions_matched = 0
    num_taken_suggestions_matched_approx = 0

    suggestion_func_cache = {}
    def get_suggestion_func(suggestion):
        key = suggestion['input'], suggestion['suggestion'], suggestion['language'], suggestion['timestamp']
        if key in suggestion_func_cache:
            return suggestion_func_cache[key]
        suggestion_func_cache[key] = get_suggestion_cursor_func(suggestion)
        return suggestion_func_cache[key]
    for suggestion in suggestions:
        get_suggestion_func(suggestion)

    # Try to label parts of the document with the Anubis suggestions. Start with the whole document
    # labeled as 'Human'. Then go through the taken suggestions in reverse order, and try to match
    # them to the document starting from the end; if we find a match, label the part of the document
    # that matches as 'Codex', splitting that part of the document into three portions: the part
    # before the match, the part that matches, and the part after the match.
    matched_suggestion_indices = []
    for sidx, suggestion in reversed(list(enumerate(suggestions))):
        if not suggestion['taken']: continue
        suggestion_text = suggestion['suggestion']
        for i in range(len(document_parts)-1, -1, -1):
            label, text, function, _ = document_parts[i]
            if label != 'Human': continue
            # This UUID is a special case where we can't get the function name
            # from the suggestion because the input was logged incorrectly.
            if args.function_level and uuid != '3533dacf-349b-4581-bc32-6b9f015199c1':
                suggestion_func = get_suggestion_func(suggestion)
                if function != suggestion_func: continue
            match_result = match_exact(text, suggestion_text)
            if match_result is None: continue
            before, match, after, _ = match_result
            document_parts[i] = ('Human', before, function, None)
            document_parts.insert(i+1, ('Codex', match, function, {'ts': suggestion['timestamp'], 'text': suggestion_text}))
            document_parts.insert(i+2, ('Human', after, function, None))
            num_taken_suggestions_matched += 1
            matched_suggestion_indices.append(sidx)
            break

    assert ''.join(part[1] for part in document_parts) == final_document

    # Remove suggestions that were matched.
    suggestions = [s for sidx, s in enumerate(suggestions) if sidx not in matched_suggestion_indices]
    # print(f"{uuid}: {num_taken_suggestions_matched}/{num_taken_suggestions} suggestions matched exactly")

    # Second pass, try to match the remaining suggestions to the document using edit distance.
    for sidx, suggestion in reversed(list(enumerate(suggestions))):
        if not suggestion['taken']: continue
        suggestion_text = suggestion['suggestion']
        for i in range(len(document_parts)-1, -1, -1):
            label, text, function, alternate = document_parts[i]
            if label != 'Human': continue
            # This UUID is a special case where we can't get the function name
            # from the suggestion because the input was logged incorrectly.
            if args.function_level and uuid != '3533dacf-349b-4581-bc32-6b9f015199c1':
                suggestion_func = get_suggestion_func(suggestion)
                if function != suggestion_func: continue
            # Compute the edit distance between the suggestion and the part of the document.
            match_result = match_approximate(text, suggestion_text)
            if match_result is None: continue
            before, match, after, distance = match_result
            document_parts[i] = ('Human', before, function, None)
            extra_info = {'ts': suggestion['timestamp'], 'text': suggestion_text, 'distance': distance}
            document_parts.insert(i+1, ('CodexApproximate', match, function, extra_info))
            document_parts.insert(i+2, ('Human', after, function, None))
            num_taken_suggestions_matched_approx += 1
            break
    # Remove any remaining Human parts that are empty.
    document_parts = [part for part in document_parts if part[1] != '']
    assert ''.join(part[1] for part in document_parts) == final_document
    # print(f"{uuid}: {num_taken_suggestions_matched_approx}/{num_taken_suggestions} suggestions matched approximately")
    matchdata = {'matched': num_taken_suggestions_matched, 'matched_approx': num_taken_suggestions_matched_approx, 'total': num_taken_suggestions}

    matched_template = sum(len(p[1]) for p in document_parts if p[0] == 'Template')
    matched_exact = sum(len(p[1]) for p in document_parts if p[0] == 'Codex')
    matched_approx = sum(len(p[1]) for p in document_parts if p[0] == 'CodexApproximate')
    matched_human = sum(len(p[1]) for p in document_parts if p[0] == 'Human')
    total = sum(len(p[1]) for p in document_parts)
    combined_matchdata['matched_template'] += matched_template
    combined_matchdata['matched_exact'] += matched_exact
    combined_matchdata['matched_approx'] += matched_approx
    combined_matchdata['matched_human'] += matched_human
    combined_matchdata['total'] += total
    combined_matchdata['suggestions_matched'] += matchdata['matched']
    combined_matchdata['suggestions_approx'] += matchdata['matched_approx']
    combined_matchdata['suggestions_total'] += matchdata['total']

    # Write to JSON file too
    js_matchdata = {}
    js_matchdata['matched_template'] = matched_template
    js_matchdata['matched_exact'] = matched_exact
    js_matchdata['matched_approx'] = matched_approx
    js_matchdata['matched_human'] = matched_human
    js_matchdata['matched_total'] = total
    js_matchdata['suggestions_matched'] = matchdata['matched']
    js_matchdata['suggestions_approx'] = matchdata['matched_approx']
    js_matchdata['suggestions_total'] = matchdata['total']
    js_matchdata['suggestions_with_funcs'] = sum(1 for s in suggestions if get_suggestion_func(s) is not None)
    js_parts = []
    for label, text, function, extra_info in document_parts:
        js_parts.append({'label': label, 'text': text, 'function': function, 'extra_info': extra_info})
    json.dump(
        {
            'uuid': uuid,
            'parts': js_parts,
            'matchdata': js_matchdata,
        },
        json_out
    )
    json_out.write('\n')

    print_document_html(uuid, document_parts, matchdata)
print_html_footer(combined_matchdata)
# Print out coverage summary to stderr
print_text_summary(combined_matchdata, file=sys.stderr)

output_file.close()
json_out.close()
