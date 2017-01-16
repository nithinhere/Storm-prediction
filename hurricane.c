/*---------------------------------------------------------------------------
   CS819 Hurricane Statistics and Forecasting
-----------------------------------------------------------------------------*/
/*=======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hurricane.h"
/*=======================================================*/

int main(int argc, char *argv[])
{
	int daily_storms[MAX_MONTHS][MAX_DAYS];

	int i;
	FILE *infilep; 
	char filename[30];
	//char *year_interested;
	header_node_t *master_header;
	node_t *data;
	char year_interested[10];
	int count;
	/* data.txt holds data file names to be processed! */
	/* Read data.txt and fill up the storm_data_files array to store the names */
	/* and call read_data for each of these data files*/

	if (argc > 1) {
		master_header = (header_node_t *)malloc(sizeof(header_node_t));
		master_header->next = NULL;
		master_header->data = NULL;
		strcpy(master_header->name, "");
		for (count = 1; count < argc; count++) {
			strcpy(year_interested, argv[count]);
			strcat(year_interested, "/");
			infilep = fopen(strcat(argv[count],"/data.txt"), "r");
			if (infilep != NULL) {
				
				while (fscanf(infilep, "%s", filename) != EOF) {
					i = read_data(year_interested, filename, master_header);
					printf("%s - %d\n", filename, i);
				}
				
			}
			fclose(infilep);
			/* sanity check just to see if we actually saved all the data items correctly */
			header_node_t *h;
			int i = 0;
			int j;
			h = master_header;
			do {
				i++;
				j = 0;
				data = h->data;
				printf("%d. %s - ", i, h->name);
				do { 
					j++;
					data = data->next;
				} while (data != h->data);
				printf("%d\n", j);
				h = h->next;
			} while (h != master_header);
			
			/* Print Summary data in output file */
			print_summary(master_header);
			printf("\n-----------------------------------------\n");
			printf("Statistics for year 2005 Hurricane Season\n");
			printf("-----------------------------------------\n");
			compute_monthly_storms(master_header, daily_storms);
			printf("\n\n");
			print_monthly_storms(daily_storms);
			printf("\n\n");
			chart_windspeed(master_header);
			printf("\n\n");
			chart_latlong(master_header);
		}
	}
	else
		printf("No files to process\n");
	return(0);
}


