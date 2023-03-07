# 2022 Study on the security implications of Large Language Model Code Assistants

This repository contains the results of the 2022 study described in the Paper: `Lost at C: A User Study on the security implications of Large Language Model Code Assistants`  Link: https://arxiv.org/pdf/2208.09727.pdf

## To reproduce the results
- create a virtual environment with python 3.8 or above
- activate the virtual environment
- install the requirements with `pip install -r requirements.txt`


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

Table 4:

This table has two rows, LoC and Bugs. The code to generate the data for this table is in the following files:

- LoC: suggestion_cover.py - This creates the HTML visualization showing which portions of the code were human written and which were suggested by the code assistant. To run:

    ```
    python suggestion_cover.py -o data/suggestion_cover.html
    ```

    This creates the files `data/suggestion_cover.html` and `data/suggestion_cover.jsonl`. At the end of the script, it also prints out the coverage statistics, which are used for the LoC line in Table 4:

    ```
    Summary:

    Coverage including template lines:
    51% Template
    30% Human
    8% Codex (exact)
    9% Codex (approx)

    Coverage excluding template lines:
    63% Human
    17% Codex (exact)
    19% Codex (approx)
    ```

- Bugs: bug_origin_all.py - This script extracts the annotations for each bug and saves them in JSONL format in `data/bug_origin_all.jsonl`. To run:

    ```
    python bug_origin_all.py
    ```

    It also prints out the statistics for the Bugs line in Table 4:

    ```
    Bug origin counts:
    Human:           356 (63.1%)
    Codex (exact):    92 (16.3%)
    Codex (approx):  112 (19.9%)
    Unknown:           4 ( 0.7%)

    Unrecorded:       55
    ```

Table 5:

- bug_origin_cwe416.py - This prints a CSV to stdout with the bug origin data for the CWE-416 "strdup" bug, which is presented in the paper in Table 5. To run:

    ```
    python bug_origin_cwe416.py
    ```

    The output is:

    ```
    uuid,origin,num_bug_in_all_suggestions,num_bugs_in_taken_suggestions,bug_count_in_final_doc
    0640,Suggestion,5,3,3
    1f1c,Document,5,0,2
    26a4,Suggestion,3,1,2
    [...]
    ```
