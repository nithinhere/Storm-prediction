/*---------------------------------------------------------------------------
   CS819 Hurricane Statistics and Forecasting
-----------------------------------------------------------------------------*/
/*=======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hurricane.h"
/*=======================================================*/


int read_data(char year_interested[], char filename[], header_node_t *header) {
	FILE *infile;
	int status;
	int i = 0;
	char actual_filename[40];
	strcpy(actual_filename, year_interested);
	infile = fopen(strcat(actual_filename,filename), "r");
	if (infile != NULL) {
		char junk[10];
		char timestr[10];
		char *month, *day, *hour;
		float latitude, longitude;
		int windspeed, pressure;
		char  description[25];
		header_node_t *h_node;
		if (strlen(header->name) > 0)
			h_node = (header_node_t *)malloc(sizeof(header_node_t));
		else
			h_node = header;
		insert_header(header, h_node, strtok(filename, "."));
		while ((fscanf(infile, "%s %f %f %s %d %d %s", junk, &latitude, &longitude, \
				timestr, &windspeed, &pressure, description) != EOF)) {
			month = strtok(timestr, "/");
			day = strtok(NULL, "/");
			hour = strtok(NULL, "/");
			hour = strtok(hour, "Z");
			node_t *data_item;
			data_item = (node_t *)malloc(sizeof(node_t));
			data_item->storm_item.latitude = latitude;
			data_item->storm_item.longitude = longitude;
			data_item->storm_item.windspeed = windspeed;
			data_item->storm_item.pressure = pressure;
			strcpy(data_item->storm_item.description, description);
			data_item->storm_item.timestamp.month = atoi(month);
			data_item->storm_item.timestamp.day = atoi(day);
			data_item->storm_item.timestamp.hour = atoi(hour);
			status = insert_item(h_node, data_item);
			i++;
		}
		fclose(infile);
	}
	return(i);
}

void print_summary(header_node_t *header) {
	FILE *out;
	node_t *data;
	int hurricane, tropical_storm;
	float min_lat, max_lat, min_long, max_long;
	int max_wind, max_wind_month, max_wind_day, max_wind_hour;
	out = fopen("Summary.txt", "w");
	header_node_t *h;
	h = header;
	do {
		data = h->data;
		min_lat = data->storm_item.latitude;
		max_lat = data->storm_item.latitude;
		min_long = data->storm_item.longitude;
		max_long = data->storm_item.longitude;
		max_wind = data->storm_item.windspeed;
		max_wind_month = data->storm_item.timestamp.month;
		max_wind_day = data->storm_item.timestamp.day;
		max_wind_hour = data->storm_item.timestamp.hour;
		hurricane = 0;
		tropical_storm = 0;

		fprintf(out, "*******************************************************************************\n");
		fprintf(out, "Name: %s\n", h->name);
		do {
			if (data->storm_item.latitude < min_lat)
				min_lat = data->storm_item.latitude;
			if (data->storm_item.longitude < min_long)
				min_long = data->storm_item.longitude;
			if (data->storm_item.latitude > max_lat)
				max_lat = data->storm_item.latitude;
			if (data->storm_item.longitude > max_long)
				max_long = data->storm_item.longitude;
			if (data->storm_item.windspeed > max_wind) {
				max_wind = data->storm_item.windspeed;
				max_wind_month = data->storm_item.timestamp.month;
				max_wind_day = data->storm_item.timestamp.day;
				max_wind_hour = data->storm_item.timestamp.hour;
			}
			if (strncmp(data->storm_item.description, "HURRICANE", strlen("HURRICANE")) == 0)
					hurricane = 1;
			if (strcmp(data->storm_item.description, "TROPICAL-STORM") == 0)
					tropical_storm = 1;
			data = data->next;
		} while (data != h->data);

		fprintf(out, "Start: %d/%d at %02d:00 hours, End: %d/%d at %02d:00 hours\n", \
			h->data->storm_item.timestamp.month, h->data->storm_item.timestamp.day, h->data->storm_item.timestamp.hour, \
			h->data->previous->storm_item.timestamp.month, h->data->previous->storm_item.timestamp.day, h->data->previous->storm_item.timestamp.hour);

		if (hurricane == 1)
			fprintf(out, "Type: Hurricane\n");
		else if (tropical_storm == 1)
			fprintf(out, "Type: Tropical Storm\n");
		else
			fprintf(out, "Type: Tropical Depression\n");

		fprintf(out, "Range: Latitude: %f to %f; Longitude: %f to %f\n", min_lat, max_lat, min_long, max_long);
		fprintf(out, "Maximum sustained winds: %d MPH on %d/%d at %02d:00 hours\n", max_wind, max_wind_month, max_wind_day, max_wind_hour);
		fprintf(out, "*******************************************************************************\n");
		printf("\n");

		h = h->next;
	} while (h != header);
	
	fclose(out);
	return;
}

void compute_monthly_storms(header_node_t *header, int daily[][MAX_DAYS]){
	int i, j;
	int month, day;
	for (i = 0; i < MAX_MONTHS; i++)
		for (j = 0; j < MAX_DAYS; j++)
			daily[i][j] = 0;

	header_node_t *h;
	node_t *data;
	h = header;
	do {
		data = h->data;
		do {
			month = data->storm_item.timestamp.month;
			if (month - MAX_MONTHS > 5) {
				break;
			}
			day = data->storm_item.timestamp.day;
			daily[month - MAX_MONTHS][day] += 1;
			data = data->next;
		} while (data != h->data);
		h = h->next;
	} while (h != header);

}

void print_monthly_storms(int daily[][MAX_DAYS]){
	int i, j;

	printf("Monthly Totals for typical Hurricane season from June 1 to November 30 (Month Vs Day)\n");
	for (j = 1; j < (MAX_DAYS * 5) + 9; j++)
		printf("-");
	printf("\n");
	printf("%9s|", "");
	for (j = 1; j < MAX_DAYS; j++) {
		printf("%3d |", j);
	}
	printf("\n");
	for (j = 1; j < (MAX_DAYS * 5) + 9; j++)
		printf("-");
	printf("\n");
	for (i = 0; i < MAX_MONTHS; i++) {
		if (i == 0)
			printf("%9s|", "June");
		else if (i == 1)
			printf("%9s|", "July");
		else if (i == 2)
			printf("%9s|", "August");
		else if (i == 3)
			printf("%9s|", "September");
		else if (i == 4)
			printf("%9s|", "October");
		else if (i == 5)
			printf("%9s|", "November");

		for (j = 1; j < MAX_DAYS; j++)
			printf("%3d |", daily[i][j]);
		printf("\n");
		for (j = 1; j < (MAX_DAYS * 5) + 9; j++)
			printf("-");
		printf("\n");
	}

}

void fill_windspeed_array(int w[][MAX_WIND], int i, int wspeed) {
	int j;
	j = wspeed / 10;
	w[i][j] += 1;
}

void chart_windspeed(header_node_t *header) {
	/* We need to create an array based on the size of the number of data files */
	/* Number of columns is 20 - each column is for 10mph going from 0 to 199 */
	/* Number of rows depends on how many data files i.e. storms we have in our data set */

	/* First get the number of data files depending on how many headers we have and then allocate */
	/* a blob of memory which represents an array of A X MAX_WIND where A is the number of data files */
	header_node_t *h;
	node_t *data;
	int *windspeed_array;
	int windspeed;
	int i, j;
	int count = 0;
	h = header;

	do {
		count++;
		h = h->next;
	} while (h != header);

	/* So now we allocate a blob representing count X 20 integers since we are interested in */
	/* maintaining an array of integers for representing windspeed quantities */

	windspeed_array = (int *)calloc(count*MAX_WIND, sizeof(int));
	h = header;
	i = 0;
	do {
		data = h->data;
		do {
			windspeed = data->storm_item.windspeed;
			fill_windspeed_array(windspeed_array, i, windspeed);
			data = data->next;
		} while (data != h->data);
		h = h->next;
		i++;
	} while (h != header);

	printf("Sustained Winds (Storm Name Vs Windspeed)\n");
	for (j = 0; j < (MAX_WIND * 6) + 8; j++)
		printf("-");
	printf("\n");
	printf("%8s|", "");
	for (j = 0; j < MAX_WIND; j++) {
		printf(" %3d |", (j * 10) + 9);
	}
	printf("\n");
	for (j = 0; j < (MAX_WIND * 6) + 8; j++)
		printf("-");
	printf("\n");

	h = header;
	do {
		printf("%8s|", h->name);
		for (j = 0; j < MAX_WIND; j++) {
			printf(" %3d |", *windspeed_array);
			windspeed_array++;
		}
		printf("\n");
		for (j = 0; j < (MAX_WIND * 6) + 8; j++)
			printf("-");
		printf("\n");
		h = h->next;
	} while (h != header);

}

void chart_latlong(header_node_t *header){
	int i, j;
	int lati, longi;
	int l[MAX_LONG][MAX_LAT] = { 0 }; /* Static array is sufficient */
	header_node_t *h;
	node_t *data;
	h = header;
	do {
		data = h->data;
		do {
			lati = data->storm_item.latitude;
			longi = fabs(data->storm_item.longitude);
			l[longi][lati] += 1;
			data = data->next;
		} while (data != h->data);
		h = h->next;
	} while (h != header);

	printf("Latitude Longitude Totals (Longitude Vs Latitude)\n");
	for (j = MIN_LAT + 11; j < (MAX_LAT * 3) + 20; j++)
		printf("-");
	printf("\n");
	printf("   |");
	for (j = MIN_LAT + 11; j < MAX_LAT; j++) 
		printf(" %2d|", j);
	printf("\n");
	for (j = MIN_LAT + 11; j < (MAX_LAT * 3) + 20; j++)
		printf("-");
	printf("\n");
	for (i = MIN_LONG; i < MAX_LONG; i++) {
		printf("%3d|", i);
		for (j = MIN_LAT+11; j < MAX_LAT; j++) {
			if (l[i][j] > 0)
				printf(" %2d|", l[i][j]);
			else
				printf("   |");
		}
		printf("\n");
		for (j = MIN_LAT + 11; j < (MAX_LAT * 3) + 20; j++)
			printf("-");
		printf("\n");
	}
}
