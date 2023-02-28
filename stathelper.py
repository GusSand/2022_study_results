import sys
import scipy.stats as stats
from itertools import combinations
import pingouin as pg

COLOR_RED = '\033[91m'
COLOR_GREEN = '\033[92m'
COLOR_YELLOW = '\033[93m'
COLOR_BLUE = '\033[94m'
COLOR_RESET = '\033[0m'
COLOR_BOLD = '\033[1m'

def significance(pvalue):
    if pvalue < 0.01:
        return "(strong evidence)"
    if pvalue < 0.05:
        return "(significant)"
    if pvalue < 0.1:
        return "(weak evidence)"
    return "(no evidence)"

def significance_color(pvalue):
    sig = significance(pvalue)
    sig = sig[1:-1]
    color = { 'strong evidence': COLOR_GREEN,
        'significant': COLOR_BLUE,
        'weak evidence': COLOR_YELLOW,
        'no evidence': COLOR_RED }[sig]
    return "(" + color + sig + COLOR_RESET + ")"

def bold_string(s):
    return COLOR_BOLD + s + COLOR_RESET

def print_stats(measure_df, measure_name, column, outfile=sys.stdout, alternative='two-sided', compare_groups=None):
    """
    measure_df: dataframe with a 'Group' column
    measure_name: name of the measure (for printing only)
    column: column in measure_df to analyze
    outfile: file to write output to
    alternative: 'two-sided', 'less', or 'greater'
    compare_groups: explicit list of pairs of groups [(G1, G2), ...] to compare
        If alternative is not 'two-sided', then compare_groups must be specified,
        because the order of the pairs matters in one-sided tests.
    """
    if alternative != 'two-sided' and compare_groups is None:
        raise ValueError(f"Can't do {alternative} test without compare_groups")
    
    # Some highlighting and colors if we are at a terminal
    if outfile.isatty():
        sigstring = significance_color
        bold = bold_string
    else:
        sigstring = significance
        bold = lambda x: x

    print(f"============= {bold(measure_name)} =============", file=outfile)
    print(measure_df.groupby('Group').agg({column: ['count', 'mean', 'median', 'std']}), file=outfile)
    print(file=outfile)
    split = dict((x,y) for (x,y) in measure_df.groupby('Group', as_index=False))
    if compare_groups is None:
        compare_groups = combinations(split.keys(),2)
    for g1, g2 in compare_groups:
        print(f'==> Stats comparing {bold(g1)} to {bold(g2)} on {measure_name}', file=outfile)
        ttest_result = stats.ttest_ind(split[g1][column], split[g2][column], equal_var=False, alternative=alternative)
        significant = sigstring(ttest_result[1])
        print(f'Welch T-test ({alternative}): {ttest_result[0]:.3f}, p-value: {ttest_result[1]:E} {significant}', file=outfile)
        mwu_result = stats.mannwhitneyu(split[g1][column], split[g2][column], alternative=alternative)
        significant = sigstring(mwu_result[1])
        print(f'Mann-Whitney U test ({alternative}): {mwu_result[0]:.3f}, p-value: {mwu_result[1]:E} {significant}', file=outfile)
        print(f'T-test from Pingouin ({alternative}):', file=outfile)
        # Confidence interval for the difference in means
        res = pg.ttest(split[g1][column], split[g2][column], paired=False, alternative=alternative)
        print(res, file=outfile)
        print(file=outfile)
