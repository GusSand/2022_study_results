import pandas as pd
import numpy as np
import scipy.stats as stats
from scipy.stats import ttest_ind_from_stats



def non_inferiority_ttest(mean1, stddev1, n1, mean2, stddev2, n2, relative_difference, 
        equal_variance=False, increase_good=True):
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
    # print (mean1)
    # print(relative_difference)
    #delta = relative_difference * mean1
    delta = 0

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

    pvalue = pval
    if increase_good:
        pvalue = pval/2.0
    else:
        #pvalue = 1 - pval/2.0
        pvalue = pval/2.0 #note that pvals should not depend on whether higher is better for worse. 
                          #easy to sanity check using std=0
    
    return tstat, pvalue


# read the tsv file into a pandas DataFrame
df = pd.read_csv('data/table3.tsv', sep='\t')

# get a list of the unique functions in the function_name column
functions = df['function_name'].unique()


print ("Compiling ======================================")
#iterate over the list of functions
for function in functions:
    
    ## Control Group
    #print("Function: " + function)
    # compiling
    function_df = df[df["function_name"] == function]
    control_comp_n = function_df[function_df["Study"] == "Control"]["N"].values[0]
    control_comp_mean = function_df[function_df["Study"] == "Control"]["RATE"].values[0]
    control_comp_std = function_df[function_df["Study"] == "Control"]["N_SEVERE_CWES_STDEV"].values[0]

    # passing
    # control_pass_n = function_df[function_df["Study"] == "Control"]["N_PASSING"].values
    # control_pass_mean = function_df[function_df["Study"] == "Control"]["RATE_PASSING_SEVERE_CWES"].values
    # control_pass_std = function_df[function_df["Study"] == "Control"]["N_SEVERE_CWES_STDEV"].values


    ## Assisted Group
    control_assisted_n = function_df[function_df["Study"] == "Assisted"]["N"].values[0]
    control_assisted_mean = function_df[function_df["Study"] == "Assisted"]["RATE"].values[0]
    control_assisted_std = function_df[function_df["Study"] == "Assisted"]["N_SEVERE_CWES_STDEV"].values[0]

    relative_difference=0.11
    increase_good=False
    equal_variance=False

    [t, p] = non_inferiority_ttest( float(control_comp_mean), float(control_comp_std), float(control_comp_n), 
                                    float(control_assisted_mean), float(control_assisted_std), float(control_assisted_n), 
                                    relative_difference, equal_variance, increase_good)

    # [t, p] = non_inferiority_ttest( float(control_assisted_mean), float(control_assisted_std), float(control_assisted_n), 
    #                                 float(control_assisted_mean), float(control_assisted_std), float(control_assisted_n), 
    #                                 relative_difference, equal_variance, increase_good)

    if p < 0.05:
        print(f'Control: Function: {function} is statistically different from the control group. Pval: {p}')
    # else:
    #     print (f'Control: Function: {function} Pval: {p}')

#     results.append({"function": function, "t": t, "p": p})


print ("Passing  ======================================")

for function in functions: 

    #print("Function: " + function)

    function_df = df[df["function_name"] == function]

    control_comp_n = function_df[function_df["Study"] == "Control"]["N_PASSING"].values[0]
    control_comp_mean = function_df[function_df["Study"] == "Control"]["RATE_PASSING_SEVERE_CWES"].values[0]
    control_comp_std = function_df[function_df["Study"] == "Control"]["N_PASSING_SEVERE_CWES_STDEV"].values[0]

    #print(f"Control: N: {control_comp_n}, Mean: {control_comp_mean}, Std: {control_comp_std}")

    control_assisted_n = function_df[function_df["Study"] == "Assisted"]["N_PASSING"].values[0]
    control_assisted_mean = function_df[function_df["Study"] == "Assisted"]["RATE_PASSING_SEVERE_CWES"].values[0]
    control_assisted_std = function_df[function_df["Study"] == "Assisted"]["N_PASSING_SEVERE_CWES_STDEV"].values[0]
    
    #print(f"Assisted: N: {control_comp_n}, Mean: {control_comp_mean}, Std: {control_comp_std}")

    relative_difference=0.11
    increase_good=False
    equal_variance=False

    [t, p] = non_inferiority_ttest( float(control_comp_mean), float(control_comp_std), float(control_comp_n), 
                                    float(control_assisted_mean), float(control_assisted_std), float(control_assisted_n), 
                                    relative_difference, equal_variance, increase_good)

    if p < 0.05:
        print(f'Function: {function} is statistically different from the control group. Pval: {p}')
        print(f"Control: N: {control_comp_n}, Mean: {control_comp_mean}, Std: {control_comp_std}")
        print(f"Assisted: N: {control_assisted_n}, Mean: {control_assisted_mean}, Std: {control_assisted_std}")
        print("")

    # else:
    #     print (f'Control: Function: {function} Pval: {p}')



# results = pd.DataFrame(results)
# print(results)