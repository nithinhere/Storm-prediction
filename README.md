# Storm-prediction

Scenario
Every year, the typical Atlantic hurricane season starts on June 1 and ends on November 30. 2005 was a
major year for tropical storms and hurricanes. Storms are given names based on their formation into a
tropical storm and the ability to sustain itself to be considered a threat of any proportions. In 2005 there
were at least 27 named storms (Katrina and Rita were two that year that had the biggest impact in terms of
destruction). http://weather.unisys.com/index.php provides a complete source of graphical weather
information as well as provide real-time and archival data for analyzing and predicting weather patterns.
The data on this site are provided from the National Weather Service via the NOAAPORT satellite data
service.
Your job as a programmer would be to look at at tropical storm and hurricane data for the year 2005 and
provide some statistical insight on it, as well as provide the ability to make some predictions.
Method
To implement this program you will use several appropriate data structures based on what’s needed. For
2005 there is storm data from 27 different storms, they are all in the same format. All of the raw data
needs to be initially stored in linked lists. All data pertaining to one storm is store in one linked list. The
headers for each linked list also form a linked list. Beyond this, several other data structures will also need
to be used to store data in a manner that is efficient to process.
Data
A sample record contains the following data as indicated below:

Record # Latitude Longitude Date/Time Wind Speed Pressure Storm Type

2 19.90 -95.80 06/29/03Z 35 1005 TROPICAL-STORM

Each storm has data in its own text file. The name of the file contains the name of the storm – for example,
Cindy.txt is the data file for the storm “Cindy”. Since we are going to process several data files, there is
one data file called “data.txt” that contains the names of each of the storm data file names, one per line.
You will be providing just the name of the year (for example 2005) to your program which will then read
the file data.txt in the folder “2005” and pick up all the file names present in that data file. You will need
to use C’s command-line argument to pick up the year (for which we are interested in) from the
command-line.

Data Structures
You must define a single type of structure that can hold all of the data fields indicated above and use this
in your array of structures. Further, since the date/timestamp information is actually made up of 3 fields in
each record you must create a separate structure to store these fields and include this structure in your
main structure. Note that the first field in the record is simply a record-keeping number and is not needed
to be stored anywhere.
Other than the basic data structure, you also need to create other data structures as appropriate based on
the requirements..
Requirements
1. The program should initially read all the data and store them in the appropriate structures. (The
Date/Time field needs to be split up into individual components).
2. A summary of the data in each data file should be printed programmatically to an output file
which includes the following pieces of information:
a. Storm name
b. Type – Hurricane, Tropical Storm, Tropical Depression (highest of the three)
c. Start and End date & time
d. Range of Latitude and Longitude
e. Maximum sustained winds with date and time
3. The program should display a table that indicates day by day storm totals for each month of the
typical hurricane season (June through November) for the entire dataset. In other words a 2D
array must be created of size 6x31 whose cells contain the total number of storms each day of the
month. For printing the contents of the table/array you must use pointer arithmetic.
4. The program should display a table that indicates totals for wind speed ranges for each storm. The
wind speed range which are the columns of the table appear in 10mph increments. While you can
use an array to store the wind speed information, since the size of the array depends on the
number of data files you will need to create the array (call it memory blob) dynamically. For
printing the contents of the table/array you must use pointer arithmetic.
5. The program should display a table that indicates storm totals for each latitude/longitude possible
for all storms combined. This will require you to define a 2D array of the appropriate size. Since a
lot of the grid area for this table will be empty you can choose to display just the portion of the
2D array (table) that contains data for the storm data that we are working with.
