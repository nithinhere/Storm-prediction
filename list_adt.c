/*---------------------------------------------------------------------------

   CS819 List ADT
-----------------------------------------------------------------------------*/
/*=======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hurricane.h"
/*=======================================================*/

int insert_item(header_node_t *header, node_t *item) {
	node_t *previous;
	if (header != NULL) {
		if (header->data == NULL) {
			header->data = item;
			item->next = item;
			item->previous = item;
		}
		else {
			previous = header->data->previous;
			item->next = header->data;
			item->previous = previous;
			previous->next = item;
			header->data->previous = item;
		}
		//printf("item %x item.next %x item.previous %x\n", item, item->next, item->previous);
		return(1);
	}
	else
		return(0);
}

int insert_header(header_node_t *header, header_node_t *header_item, char name[]) {
	header_node_t *h_node;
	if (strlen(header->name) == 0) {
		header->next = header;
		header->data = NULL;
		strcpy(header->name, name);
	}
	else {
		h_node = header;
		int i = 1;
		while (h_node->next != header) {
			i++;
			h_node = h_node->next;
		}
		h_node->next = header_item;
		header_item->data = NULL;
		strcpy(header_item->name, name);
		header_item->next = header;
	}
	return(1);
}
