#!/usr/bin/env python

from collections import defaultdict
import sys
import subprocess
import json

TIMEOUT = 10

def run_test(test, suite):
    try:
        res = subprocess.run([
            f'{suite}/{test}.bin'],
            stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            timeout=TIMEOUT
        )
        report = {
            'return_code': res.returncode,
            'stdout': res.stdout.decode('utf-8', errors='backslashreplace'),
            'stderr': res.stderr.decode('utf-8', errors='backslashreplace'),
            'passed': res.returncode == 0,
            'skipped': False,
        }
    except subprocess.TimeoutExpired as e:
        report = {
            'return_code': 'timeout',
            'stdout': e.stdout.decode('utf-8', errors='backslashreplace') if e.stdout else '',
            'stderr': e.stderr.decode('utf-8', errors='backslashreplace') if e.stderr else '',
            'passed': False,
            'skipped': False,
        }
    return report

if len(sys.argv) != 2 or sys.argv[1] not in ('tests_orig', 'tests_ref'):
    print('Usage: run_testsuite.py [tests_orig|tests_ref]')
    sys.exit(1)
suite = sys.argv[1]

results = {}
results['results'] = {}

# Full test suite
all_tests = []
# Load mapping between test names and tested API function
apis = {}
for line in open(f"{suite}/all_tests.txt"):
    test, api = line.strip().split()
    apis[test] = api
    all_tests.append(test)
# "Functional" tests that don't test things like NULL inputs
functional_tests = []
for line in open(f"{suite}/functional.txt"):
    test = line.strip()
    functional_tests.append(test)

# Tests that we skip
api_report = json.load(open(f'api_report.json'))

for test in all_tests:
    if api_report[apis[test]] != 'ok':
        results['results'][test] = {
            'return_code': f'skipped: {api_report[apis[test]]}',
            'stdout': '',
            'stderr': '',
            'passed': False,
            'skipped': True,
        }
    else:
        res = run_test(test, suite)
        results['results'][test] = res

passed = 0
for test in all_tests:
    if results['results'][test]['passed']:
        passed += 1
results['passed'] = passed
results['total'] = len(all_tests)
passed_functional = 0
for test in functional_tests:
    if results['results'][test]['passed']:
        passed_functional += 1
results['passed_functional'] = passed_functional
results['total_functional'] = len(functional_tests)

print(json.dumps(results, indent=4))
print(f"SUMMARY: Passed: {passed} / {len(all_tests)}, Passed functional: {passed_functional} / {len(functional_tests)}", file=sys.stderr)
print(f"Detailed results:", file=sys.stderr)
for test in all_tests:
    res = results['results'][test]
    status = f'SKIPPED ({api_report[apis[test]]})' if res['skipped'] else 'PASSED' if res['passed'] else 'FAILED'
    print(f"{test:<60s} {status}", file=sys.stderr)
