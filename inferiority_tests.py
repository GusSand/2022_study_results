import pandas as pd
from scipy.stats import ttest_ind_from_stats
import numpy as np


def non_inferiority_ttest(mean1, stddev1, n1, mean2, stddev2, n2, relative_difference, equal_variance=False, increase_good=True):
    '''
    Perform a one-sided t-test with a non-inferiority threshold for two independent samples.
    mean1/2: group mean
    stddev1/2: standard deviation of each group
    n1/2: number of observations in each group
    relative_difference: threshold as a percentage of the base group (e.g. 0.1=10% difference)
    equal_variance: if False, uses Welch's t-test.
    increase_good: if True, Ho: mean2 <= mean1 - threshold. Else Ho: mean2 >= mean1 + threshold.
    Returns: 
    '''
    
    delta = relative_difference * mean1

    if increase_good:
        threshold = mean1 - delta
    else:
        threshold = mean1 + delta

    tstat, pval = ttest_ind_from_stats(mean1=threshold, 
                                       std1=stddev1, 
                                       nobs1=n1, 
                                       mean2=mean2, 
                                       std2=stddev2, 
                                       nobs2=n2, 
                                       equal_var=equal_variance)

    if increase_good:
        pvalue = pval/2.0
    else:
        #pvalue = 1 - pval/2.0
        pvalue = pval/2.0 #note that pvals should not depend on whether higher is better for worse. 
                          #easy to sanity check using std=0
    
    return tstat, pvalue

def print_stats(filename, field):

    df = pd.read_csv(filename)

    df_control = df[df['Group'] == field]
    mu = df_control['Bugs per LoC'].mean()
    std = df_control['Bugs per LoC'].std()
    n = df_control['Bugs per LoC'].count()

    print(f'{field}: {filename} mean: {mu} std:{std} n: {n}')
    
    return mu, std, n



relative_difference=0.11
increase_good=False
equal_variance=False

print('Per Loc Compiled')
filename = 'data/derived_data/bugs_per_loc_compiled.csv'
mu1, std1, n1 = print_stats(filename, 'Control')
mu2, std2, n2 = print_stats(filename, 'Assisted')
[ttest, pval] = non_inferiority_ttest(mu1, std1, n1, mu2, std2, n2, relative_difference, equal_variance, increase_good)
print (f'Pval: {pval}')

print("====================================")


print('Per Loc Severe Compiled')
filename = 'data/derived_data/bugs_per_loc_severe_compiled.csv'
mu1, std1, n1 = print_stats(filename, 'Control')
mu2, std2, n2 = print_stats(filename, 'Assisted')
[ttest, pval] = non_inferiority_ttest(mu1, std1, n1, mu2, std2, n2, relative_difference, equal_variance, increase_good)
print (f'Pval: {pval}')

print("====================================")


print('Per Loc passing')
filename = 'data/derived_data/bugs_per_loc_passing.csv'
mu1, std1, n1 = print_stats(filename, 'Control')
mu2, std2, n2 = print_stats(filename, 'Assisted')
[ttest, pval] = non_inferiority_ttest(mu1, std1, n1, mu2, std2, n2, relative_difference, equal_variance, increase_good)
print (f'Pval: {pval}')

print("====================================")


print('Per Loc Severe Passing')
filename = 'data/derived_data/bugs_per_loc_severe_passing.csv'
mu1, std1, n1 = print_stats(filename, 'Control')
mu2, std2, n2 = print_stats(filename, 'Assisted')
[ttest, pval] = non_inferiority_ttest(mu1, std1, n1, mu2, std2, n2, relative_difference, equal_variance, increase_good)
print (f'Pval: {pval}')


