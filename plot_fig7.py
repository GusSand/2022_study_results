#!/usr/bin/env python

import json
import os
import sys
import pandas as pd
import seaborn as sns
import numpy as np
import glob
import matplotlib
# Set the font type to be Type 42 (TrueType) so that the fonts are editable in Adobe Illustrator
matplotlib.rcParams['pdf.fonttype'] = 42
matplotlib.rcParams['ps.fonttype'] = 42
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
from stathelper import print_stats
import warnings

# Suppress warnings
warnings.filterwarnings('ignore')

basic_test_map = {
    # 'list_init': ['test_list_init'],
    'list_add_item_at_pos': ['test_list_add_item_at_pos'],
    'list_item_to_string': ['test_list_item_to_string'],
    'list_print': ['test_list_print'],
    'list_update_item_at_pos': ['test_list_update_item_at_pos'],
    'list_remove_item_at_pos': ['test_list_remove_item_at_pos'],
    'list_swap_item_positions': ['test_list_swap_item_positions'],
    'list_find_highest_price_item_position': ['test_list_find_highest_price_item_position'],
    'list_cost_sum': ['test_list_cost_sum'],
    'list_save': ['test_list_save'],
    'list_load': ['test_list_load'],
    'list_deduplicate': ['test_list_deduplicate']
}

expanded_test_map = {
    # 'list_init': ['test_list_init', 'test_list_init_nullhead'],
    'list_add_item_at_pos': ['test_list_add_item_at_pos', 'test_list_add_item_at_pos_nullhead', 'test_list_add_item_at_pos_nullitem', 'test_list_add_item_at_pos_oob'],
    'list_item_to_string': ['test_list_item_to_string', 'test_list_item_to_string_nullhead', 'test_list_item_to_string_nullstr', 'test_list_item_to_string_longstr'],
    'list_print': ['test_list_print', 'test_list_print_nullhead', 'test_list_print_longitem'],
    'list_update_item_at_pos': ['test_list_update_item_at_pos', 'test_list_update_item_at_pos_nullhead', 'test_list_update_item_at_pos_nullstr', 'test_list_update_item_at_pos_oob'],
    'list_remove_item_at_pos': ['test_list_remove_item_at_pos', 'test_list_remove_item_at_pos_nullhead', 'test_list_remove_item_at_pos_oob'],
    'list_swap_item_positions': ['test_list_swap_item_positions', 'test_list_swap_item_positions_samepos', 'test_list_swap_item_positions_nullhead', 'test_list_swap_item_positions_oob'],
    'list_find_highest_price_item_position': ['test_list_find_highest_price_item_position', 'test_list_find_highest_price_item_position_nullhead', 'test_list_find_highest_price_item_position_nullpos'],
    'list_cost_sum': ['test_list_cost_sum', 'test_list_cost_sum_nullhead', 'test_list_cost_sum_nulltotal'],
    'list_save': ['test_list_save', 'test_list_save_nullhead', 'test_list_save_nullfilename', 'test_list_save_badfile'],
    'list_load': ['test_list_load', 'test_list_load_nullhead', 'test_list_load_nullfilename', 'test_list_load_longitem', 'test_list_load_badparse', 'test_list_load_badfile', 'test_list_load_missingfile'],
    'list_deduplicate': ['test_list_deduplicate', 'test_list_deduplicate_nullhead', 'test_list_deduplicate_single', 'test_list_deduplicate_nodups']
}

def load_active_inactive(active_inactive_txt):
    with open(active_inactive_txt) as fd:
        return {line.split()[0]: line.strip().split()[1] for line in fd.readlines()}

def make_rows(uuid, active_inactive, bug_data=None):
    rows = []
    repo_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), f'raw_data/{uuid}')
    if not os.path.exists(repo_dir):
        return []
    # Handle the Codex autopilot case
    if uuid not in active_inactive:
        if uuid.startswith('cushman') or uuid.startswith('davinci'):
            group = 'Autopilot'
        else:
            raise ValueError(f'Unknown UUID {uuid}')
    else:
        group = 'Assisted' if active_inactive[uuid] == 'Active' else 'Control'
    basic_test_results = json.load(open(os.path.join(repo_dir, 'orig_testsuite.json')))
    expanded_test_results = json.load(open(os.path.join(repo_dir, 'ref_testsuite.json')))
    api_report = json.load(open(os.path.join(repo_dir, 'api_report.json')))
    # list_init is ignored because no one modified it
    del api_report['list_init']
    api_functions = list(api_report.keys())
    for func in api_functions:
        row = {}
        row['UUID'] = uuid
        row['Group'] = group
        row['Function'] = func
        if bug_data is not None:
            bug_data_func = bug_data.get(func, None)
            manually_marked_unimplemented = bug_data_func['notes'].startswith('UNIMPLEMENTED') if bug_data_func else False
            row['API Implemented'] = api_report[func] == 'ok' and not manually_marked_unimplemented
        else:
            row['API Implemented'] = api_report[func] == 'ok'
        row['Failed Compile'] = api_report[func] == 'compile_error'
        for test in basic_test_map[func]:
            row['basic_' + test] = basic_test_results['results'][test]['passed']
        for test in expanded_test_map[func]:
            row['expanded_' + test] = expanded_test_results['results'][test]['passed']
        rows.append(row)
    return rows

def create_functionality_dataframe(bug_finding_json, active_inactive_file):
    active_inactive = load_active_inactive(active_inactive_file)
    bug_data_all = json.load(open(bug_finding_json))
    repo_uuids = set(map(os.path.basename, glob.glob('raw_data/*-*-*-*')))
    if len(repo_uuids) < 1:
        raise ValueError(f'No REPOS!!!')
    rows = []
    for uuid in bug_data_all:
        bug_data = bug_data_all[uuid]
        rows += make_rows(uuid, active_inactive, bug_data)
    # Need to finally add in any users who weren't in the spreadsheet and hence
    # didn't make it into bug_finding.json
    remaining_uuids = repo_uuids - set(bug_data_all)
    for uuid in remaining_uuids:
        rows += make_rows(uuid, active_inactive)
    return pd.DataFrame(rows)

def get_functionality_percentages(df):
    percent_compiled = (100*(11 - df.groupby(['Group','UUID'])[['Failed Compile']].sum()) / 11).reset_index().rename(columns={'Failed Compile': 'Percentage'})
    percent_compiled['Measure'] = 'Compiled'
    assert percent_compiled['Percentage'].max() <= 100
    assert percent_compiled['Percentage'].min() >= 0

    groupsum = df.groupby(['Group','UUID'])[['API Implemented']].sum()
    percent_implemented = (100*groupsum.sum(axis=1) / 11).reset_index().rename(columns={0: 'Percentage'})
    percent_implemented['Measure'] = 'Implemented'
    assert percent_implemented['Percentage'].max() <= 100
    assert percent_implemented['Percentage'].min() >= 0

    column_list = ['basic_'+t for t in sum(basic_test_map.values(), start=[])]
    groupsum = df.groupby(['Group','UUID'])[column_list].sum()
    percent_passed_basic = (100*groupsum.sum(axis=1) / len(column_list)).reset_index().rename(columns={0:'Percentage'})
    percent_passed_basic['Measure'] = 'Basic Tests'
    assert percent_passed_basic['Percentage'].max() <= 100
    assert percent_passed_basic['Percentage'].min() >= 0

    column_list = ['expanded_'+t for t in sum(expanded_test_map.values(), start=[])]
    groupsum = df.groupby(['Group','UUID'])[column_list].sum()
    percent_passed_expanded = (100*groupsum.sum(axis=1) / len(column_list)).reset_index().rename(columns={0:'Percentage'})
    percent_passed_expanded['Measure'] = 'Expanded Tests'
    assert percent_passed_expanded['Percentage'].max() <= 100
    assert percent_passed_expanded['Percentage'].min() >= 0

    return (percent_compiled, percent_implemented, percent_passed_basic, percent_passed_expanded)

def print_functionality_stats(df, outfile):
    (percent_compiled, percent_implemented,
     percent_passed_basic, percent_passed_expanded) = get_functionality_percentages(df)
    for measure_df in (percent_compiled, percent_implemented,
                       percent_passed_basic, percent_passed_expanded):
        print_stats(measure_df, measure_df.iloc[0]['Measure'], 'Percentage', outfile)

def create_functionality_plot(df, title, filename):
    (percent_compiled, percent_implemented,
     percent_passed_basic, percent_passed_expanded) = get_functionality_percentages(df)

    full = pd.concat([percent_compiled, percent_implemented, percent_passed_basic, percent_passed_expanded], ignore_index=True)

    plot = sns.catplot(x='Group', y='Percentage', hue='Measure', data=full, kind='bar', legend=False, height=12,
                       aspect=24/12, order=['Control', 'Assisted', 'Autopilot'])
    # Rotate tick labels
    plt.xlabel('');

    # Bump up all the font sizes
    plt.ylabel('Percentage', fontsize=50);
    plt.legend(bbox_to_anchor=(0.1, .9, 1., .102), loc='lower left', ncol=2, columnspacing=1, fontsize=50, frameon=False);
    plt.xticks(fontsize=50);
    plt.yticks(fontsize=50);
    plt.tight_layout()
    plt.savefig(filename)

def create_security_plot(df, title, filename):

    fig = plt.figure(figsize=(24,18))
    ax = plt.axes()

    df = df.copy()
    df['Function'] = df['Function'].str.replace('list_', '', regex=True)

    print('before')
    print(df['Group'].value_counts())
    df['Group'] = df['Group'].replace('Codex', 'Assisted').replace('Non-Codex','Control')
    print('after')
    print(df['Group'].value_counts())

    ## Great Trick: make the group a categorical variable and give it the order to have the correct order
    #df["Group"] = pd.Categorical(df["Group"],  ["Control", "Assisted", "Autopilot"], ordered=True)

    grouped_df = df.groupby(['Function', 'Group', 'UUID'])
    # Get the number of total bugs per user, for each function and group
    grouped_sum = grouped_df['Bug Count'].sum().reset_index().sort_values(by=['Bug Count', 'Function'], ascending=False)
    # Make a bar plot
    sns.barplot(x='Function', y='Bug Count', hue='Group', data=grouped_sum, ax=ax)

    # No Title or xlabel
    ax.set_title('Percentage CWEs per Function and Group', fontsize=50)
    plt.xlabel('');

    # fix up the legend
    plt.legend(bbox_to_anchor=(0.1, .91, 1., .102), loc='upper left', fontsize=40, frameon=False, ncol=3, columnspacing=1)#, bbox_to_anchor=(0.2, .8, 0., 0));

    # Rotate tick labels & increase font size
    ax.set_xticklabels(ax.get_xticklabels(), rotation=-45, ha='left',fontsize=25, wrap=True)

    # bump up all the font sizes
    plt.ylabel('');
    plt.yticks(fontsize=40, );
    ax.yaxis.set_major_formatter(mtick.PercentFormatter())

    # remove the top and right spines
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.tight_layout()
    plt.savefig(filename)


####################################################################################################
##
## This code creates figure 7 in the paper. 
## We called it there functionality.pdf
##
if __name__ == "__main__":


    df = create_functionality_dataframe("data/bug_finding.json", "data/active_inactive.txt")
    df.to_csv('functional_tests.csv', index=False)
    # Write out the functionality stats
    with open('data/functionality_stats.txt', 'w') as outfile:
        print_functionality_stats(df, outfile)

    sns.set_style("whitegrid")

    ## Create the functionality plots
    #sns.set_style("whitegrid")
    create_functionality_plot(df, 'Functionality', 'figures/functionality.pdf')
    print('\nCreated FIG7 as figures/functionality.pdf')

    ## Create the security plots
    # df_bug_finding = pd.read_csv('bug_finding_flat.csv')
    # create_security_plot(df_bug_finding, '', 'figures/security_analysis.pdf')
