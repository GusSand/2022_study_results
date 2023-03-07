import json
import subprocess

def read_bug_annotations(data_dir='raw_data/recombined_list_files/Active'):
    # Read the bug annotations from the list.c files using... grep
    bug_data = subprocess.check_output('grep "// bug [0-9]" *.c', shell=True, cwd=data_dir, text=True)
    return bug_data.split('\n')

# Example lines:
# 0640be89-ee5f-4846-8e14-40fdc574d7d3-list.c:    // bug 1: id-141, omitted, approx-0.06, missing check for str == NULL
# 0640be89-ee5f-4846-8e14-40fdc574d7d3-list.c:    // bug 2: id-143, present, approx-0.06, Use of sprintf instead of snprintf for str with MAX_LEN
# 0640be89-ee5f-4846-8e14-40fdc574d7d3-list.c:    // bug 3: id-142, omitted, approx-0.06, does not check if str is NULL before print
# 0640be89-ee5f-4846-8e14-40fdc574d7d3-list.c:    // bug 1: id-294, omitted, human, doesn't initialize temporary char* buf

counts = {}
counts['human'] = 0
counts['approx'] = 0
counts['exact'] = 0
counts['unknown'] = 0
counts['unrecorded'] = 0
of = open('data/bug_origin_all.jsonl', 'w')
for line in read_bug_annotations():
    if not line: continue
    uuid, _, data = line.split(':',2)
    uuid = uuid.replace('-list.c', '')
    data = data.strip()
    bugid, bugpres, blame, desc = line.split(',', 3)
    bugid = bugid.split(':')[1].strip()
    bugpres = bugpres.strip()
    blame = blame.strip()
    desc = desc.strip()
    print(json.dumps({'uuid': uuid, 'bugid': bugid, 'bugpres': bugpres, 'blame': blame, 'desc': desc}), file=of)
    if blame == 'human' or blame == 'humanf':
        # Human
        counts['human'] += 1
    elif blame.startswith('approx'):
        # Codex (approximate match)
        counts['approx'] += 1
    elif blame == 'codex':
        # Codex (exact match)
        counts['exact'] += 1
    elif blame == 'unknown':
        # Unknown (we couldn't determine the origin)
        counts['unknown'] += 1
    elif blame == 'unrecorded':
        # Unrecorded (skipped because data was invalid)
        counts['unrecorded'] += 1
    else:
        raise ValueError(f"{uuid} Unknown blame type {blame}")
of.close()

# Ignore unrecorded
total = sum(counts.values()) - counts['unrecorded']
print("Bug origin counts:")
print(f"Human:           {counts['human']:3d} ({counts['human']/total*100:4.1f}%)")
print(f"Codex (exact):   {counts['exact']:3d} ({counts['exact']/total*100:4.1f}%)")
print(f"Codex (approx):  {counts['approx']:3d} ({counts['approx']/total*100:4.1f}%)")
print(f"Unknown:         {counts['unknown']:3d} ({counts['unknown']/total*100:4.1f}%)")
print()
print(f"Unrecorded:      {counts['unrecorded']:3d}")
