import sqlite3
import math

DATABASE_NAME = "./data/bugs_and_demographics.sqlite3"
OUTPUT_NAME = "./data/derived_data/table7.tsv"

QUERY = """
--this calculates table 7
select 
	functions_marked.function_name,
	active_inactive.Study,
	bug_classes.consequence_cwe as consequence_cwe,
	
	table_iii.N as N, --so that N is correct we have to sum it using a subquery
	sum(CASE WHEN bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END) as N_THIS_CWE,
	round(sum(CASE WHEN bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END)*1.0/table_iii.N,2) as THIS_RATE,
	
	table_iii.N_PASSING as N_PASSING,
	sum(CASE WHEN functions_marked.basic_test_passed == 1 AND bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END) as N_PASSING_THIS_CWE,
	round(sum(CASE WHEN functions_marked.basic_test_passed == 1 AND bug_classes.consequence_cwe_top_25_rank is not null then bugs_found.count else 0 END)*1.0/table_iii.N_PASSING*1.0,2) as THIS_PASSING_RATE 
	
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
left JOIN
(select --this is the subquery to calculate N and N_PASSING for each of the function_name/Study pairs
	functions_marked.function_name as function_name,
	active_inactive.Study as Study,
	count(DISTINCT active_inactive.audit_id) AS N,
	count(DISTINCT CASE when functions_marked.basic_test_passed == 1 then active_inactive.audit_id else NULL END) AS N_PASSING,
	sum(bugs_found.count) as N_CWEs
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
group by functions_marked.function_name, active_inactive.Study
) as table_iii
on
	table_iii.function_name == functions_marked.function_name AND
	table_iii.Study == active_inactive.Study
where consequence_cwe_top_25_rank is not null
group by functions_marked.function_name, active_inactive.Study, bug_classes.consequence_cwe
order by functions_marked.function_name,
	case 
	when active_inactive.Study == "Control" then 1 
	WHEN active_inactive.Study == "Assisted" then 2
	else 3
	END
	
"""


with sqlite3.connect(DATABASE_NAME) as connection:
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

    
    