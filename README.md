# 2022 Study on the security implications of Large Language Model Code Assistants

This repository contains the results of the 2022 study described in the Paper: `Lost at C: A User Study on the security implications of Large Language Model Code Assistants`  Link: https://arxiv.org/pdf/2208.09727.pdf

## Data
The data folder contains all the data used by the python scripts to recreate the plots. There's also the raw data folder which contains the raw data from the study and it's also used by some of the scripts. 

## Code
The code used to generate the figures on the paper is in the following files: 

Figure 7:

- plot_fig7.py - Uses the data from the raw_data folder to generate figure 7. It's called functionality.pdf in the figures folder.

Figure 8:

- plot_fig8.py - Uses the data from the data folder to generate figure 8 which contains 4 figures. 2 figures for bugs per lines of code that compile: bugs_per_loc_compiled and bugs_per_loc_severe_compiled. In additions there are also two figures for lines of code that pass tests: bugs_per_loc_passing and bugs_per_loc_severe_passing.

Figure 9:

- plot_fig9.py - Uses the data from the data folder to generate figure 9. It's called cwe_prevalence.pdf in the figures folder.


plot_time_data.py - Uses the data from the data folder to generate a histogram for the time that the students took to finalize the study. It's called histogram_of_study_duration.pdf in the figures folder.


Inferioririty_per_func.py - Code to reproduce the inferiority tests. 