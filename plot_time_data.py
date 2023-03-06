import seaborn as sns
import pandas as pd
from datetime import datetime, timedelta
import matplotlib
matplotlib.rcParams['pdf.fonttype'] = 42
matplotlib.rcParams['ps.fonttype'] = 42
import matplotlib.pyplot as plt

def parse_date_to_hours(duration_str):
    
    #print(duration_str)

    # Split the string on ',' and '.' to get the days and time parts
    parts = duration_str.split(',')
    days = 0
    if len(parts) > 1:
        days = int(parts[0].split(' ')[0])
        time_parts = parts[1].split('.')[0].split(':')
    else:
        time_parts = parts[0].split('.')[0].split(':')

    # Create a base datetime object representing the start of the day
    base_datetime = datetime(1970, 1, 1)

    # Create a datetime object for the duration
    duration_datetime = base_datetime + timedelta(days=days, hours=int(time_parts[0]), minutes=int(time_parts[1]), seconds=int(time_parts[2]))

    # Calculate the difference in hours
    duration_hours = (days*24) + duration_datetime.hour + (duration_datetime.minute / 60) + (duration_datetime.second / 3600)

    #print(duration_hours)
    return (duration_hours)


def parse_date_to_days(duration_str):
        
    #print(duration_str)

    # Split the string on ',' and '.' to get the days and time parts
    parts = duration_str.split(',')
    days = 0
    if len(parts) > 1:
        days = int(parts[0].split(' ')[0])
        time_parts = parts[1].split('.')[0].split(':')
    else:
        time_parts = parts[0].split('.')[0].split(':')

    # Create a base datetime object representing the start of the day
    base_datetime = datetime(1970, 1, 1)

    # Create a datetime object for the duration
    duration_datetime = base_datetime + timedelta(days=days, hours=int(time_parts[0]), minutes=int(time_parts[1]), seconds=int(time_parts[2]))

    # Calculate the difference in hours
    duration_days = (days) + duration_datetime.hour/24 + (duration_datetime.minute / 1440) + (duration_datetime.second / 86400)

    #print(duration_hours)
    return (duration_days)


## Also test the function because datetime objects are nasty AF.
def test_parse_date_to_days():

    print('Testing parse_date_to_days()...')

    print('0 days...')
    assert parse_date_to_days('0 days, 0:00:00.123456') == 0

    print('1 days and 2 hours...')
    assert parse_date_to_days('1 days, 2:00:00.123456') == 1.0833333333333333
    
    print('30 hours...')
    assert parse_date_to_days('1 days, 6:00:00.123456') == 1.25

    print('0 days, 0:17:41')
    assert(parse_date_to_days('0 days, 0:17:41') == 0.012280092592592592)

    print('without days: 0:17:41')
    assert(parse_date_to_days('0:17:41') == 0.012280092592592592)

    print('test_parse_date_to_days ALL TESTS PASS!')

## Test the function
## because datetime objects are nasty AF. 
## we'll just test the number of hours
def test_parse_date_to_hours():
    print('Testing parse_date_to_hours()...')

    print('0 days...')
    assert parse_date_to_hours('0 days, 0:00:00.123456') == 0
    print('1 days and 2 hours...')
    assert parse_date_to_hours('1 days, 2:00:00.123456') == 26
    print('30 hours...')
    assert parse_date_to_hours('1 days, 6:00:00.123456') == 30

    print('0 days, 0:17:41')
    assert(parse_date_to_hours('0 days, 0:17:41') == 0.2947222222222222)

    print('without days: 0:17:41')
    assert(parse_date_to_hours('0:17:41') == 0.2947222222222222)


    print('test_parse_date_to_days ALL TESTS PASS!')



def plot_time_data():
    # Read the csv file into a pandas DataFrame
    df = pd.read_csv('data/histogram_data_study.csv')
    #df.describe()


    # Convert the duration column from minutes to hours
    df['duration_hours'] = df['duration'].apply(parse_date_to_days)

    # Filter the dataframe to get the rows for each group of the "Study" column
    active_group = df[df['Study'] == 'Active']
    deactive_group = df[df['Study'] == 'Deactive']

    fig = plt.figure(figsize=(18,10))
    ax = plt.axes()

    # Plot a histogram using seaborn
    # Plot the histograms
    # sns.histplot(x=active_group['duration_hours'], bins=20, label='Active', color='red', alpha=0.7)
    # sns.histplot(x=deactive_group['duration_hours'], bins=20, label='Deactive', color='blue', alpha=0.7)

    # Plot histograms on the same plot, but with different colors
    #ax = sns.histplot(x='duration_hours', data=df, hue='Study', bins=30)
    #ax = sns.histplot(x='duration_hours', data=df, hue='UG_PG', bins=30)
    # Plot the CDFs
    # sns.kdeplot(data=active_group['duration_hours'], cumulative=True, label='Active', color='red')
    # sns.kdeplot(data=deactive_group['duration_hours'], cumulative=True, label='Deactive', color='blue')

    #sns.ecdfplot(data=df, x='duration_hours', hue='Study', alpha=.5, linewidth = 7,  stat='count', ax =ax)
    sns.ecdfplot(data=df, x='duration_hours', hue='Study', alpha=.5, linewidth = 7, stat='proportion', ax =ax)


    #sns.displot(data=df, x='duration_hours', hue='Study', kind="kde", alpha=.5, bw_adjust=2, multiple="stack")
    plt.legend(labels=['Assisted', 'Control'])
    plt.setp(ax.get_legend().get_texts(), fontsize='32') # for legend text
    plt.setp(ax.get_legend().get_title(), fontsize='0') # for legend title


    ax.set_xlabel('Duration (days)', fontsize=40)
    ax.set_ylabel('Proportion', fontsize=40)
    ax.set_title('Duration by study group', fontsize=50)
    plt.xticks(fontsize=30);
    plt.yticks(fontsize=30);



    # Save the plot as an image file
    filename = 'figures/histogram_of_study_duration_days.pdf'
    plt.tight_layout()
    plt.savefig(filename)
    print(f'Done. Saved {filename}')

# Show the plot
#sns.show()


#main function
if __name__ == '__main__':
    #test_parse_date_to_hours()
    #test_parse_date_to_days()
    plot_time_data()
