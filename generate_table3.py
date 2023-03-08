import sqlite3
import math

class StdevFunc:
    def __init__(self):
        self.M = 0.0
        self.S = 0.0
        self.k = 1

    def step(self, value):
        if value is None:
            return
        tM = self.M
        self.M += (value - tM) / self.k
        self.S += (value - tM) * (value - self.M)
        self.k += 1

    def finalize(self):
        if self.k < 3:
            return None
        return math.sqrt(self.S / (self.k-2))

DATABASE_NAME = "./data/bugs_and_demographics.sqlite3"
OUTPUT_NAME = "./data/derived_data/table3.tsv"

QUERY = """
--this query makes table III
select 
	functions_marked.function_name,
	active_inactive.Study,
	count(DISTINCT active_inactive.audit_id) AS N,
	sum(CASE WHEN bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END) as N_SEVERE_CWES,
	stdev(CASE WHEN bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END) as N_SEVERE_CWES_STDEV,
	round(sum(CASE WHEN bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END)*1.0/count(DISTINCT active_inactive.audit_id),2) as RATE,
	
	count(DISTINCT CASE when functions_marked.basic_test_passed == 1 then active_inactive.audit_id else NULL END) AS N_PASSING,
	sum(CASE WHEN functions_marked.basic_test_passed == 1 AND bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END) as N_PASSING_SEVERE_CWES,
	stdev(CASE WHEN functions_marked.basic_test_passed == 1 AND bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END) as N_PASSING_SEVERE_CWES_STDEV,
	round(sum(CASE WHEN functions_marked.basic_test_passed == 1 AND bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END)*1.0/count(DISTINCT CASE when functions_marked.basic_test_passed == 1 then active_inactive.audit_id else NULL END)*1.0,2) as RATE_PASSING_SEVERE_CWES 
	
from 
	functions_marked
inner JOIN
	active_inactive
on
	active_inactive.audit_id == functions_marked.audit_id
left JOIN
	bugs_found 
on
	bugs_found.audit_id == functions_marked.audit_id and bugs_found.function_name == functions_marked.function_name
left JOIN
	bug_classes
on 
	bug_classes.id == bugs_found.bug_id
WHERE
	active_inactive.`Used in study` == "TRUE"
group by functions_marked.function_name, active_inactive.Study
order by functions_marked.function_name,
	case 
	when active_inactive.Study == "Control" then 1 
	WHEN active_inactive.Study == "Assisted" then 2
	else 3
	END
"""


with sqlite3.connect(DATABASE_NAME) as connection:
    connection.create_aggregate("stdev", 1, StdevFunc)
    cursor = connection.cursor()
    cursor.execute(QUERY)

    #create the output file
    with open(OUTPUT_NAME, "w") as output:
        #print the header
        output.write("\t".join([x[0] for x in cursor.description]))
        output.write("\n")
        for row in cursor:
            output.write("\t".join([str(x) for x in row]))
            output.write("\n")

    
    