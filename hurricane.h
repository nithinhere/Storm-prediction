/*---------------------------------------------------------------------------
   CS819 Hurricane Statistics and Forecasting
-----------------------------------------------------------------------------*/

#define MAX_NAME 31

#define MAX_DAYS 32
#define MAX_MONTHS 6
#define MAX_WIND 20
#define MIN_LAT 0
#define MAX_LAT 50
#define MIN_LONG 0
#define MAX_LONG 110

#define FILENAME_LENGTH 30

typedef struct {
	int year;
	int month;
	int day;
	int hour;
} datetime_t;

typedef struct {
	datetime_t timestamp;
	float latitude;
	float longitude;
	int   windspeed;
	int	  pressure;
	char  description[25];
} storm_detail_t;

typedef struct node node_t;

struct node {
	node_t *next;
	node_t *previous;
	storm_detail_t storm_item;
};

typedef struct header_node header_node_t;

struct header_node {
	node_t *data;
	header_node_t *next;

	char name[MAX_NAME];
};

typedef struct {
	char name[25];
	int  size;
} storm_name_t;

int insert_item(header_node_t *header, node_t *item);

int insert_header(header_node_t *header, header_node_t *header_node, char name[]);

int read_data(char *year_interested, char filename[], header_node_t *header);

void print_summary(header_node_t *header);

void compute_monthly_storms(header_node_t *header, int daily[][MAX_DAYS]);

void print_monthly_storms(int daily[][MAX_DAYS]);

void chart_windspeed(header_node_t *header);

void fill_windspeed_array(int windspeed_array[][MAX_WIND], int row, int wspeed);

void chart_latlong(header_node_t *header);
