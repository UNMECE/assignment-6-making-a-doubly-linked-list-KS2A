#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "coordinate.h"

void add_coordinate(Coordinate *list_end, float x, float y){
	Coordinate* new_coord = (Coordinate*)malloc(sizeof(Coordinate));
	int count = 0;

	new_coord->x = x;
	new_coord->y = y;
	new_coord->coord_id = ++count;
	new_coord->next = NULL;
	new_coord->previous = list_end;
}

void forward_display(Coordinate *list_beginning){
	Coordinate* temp = list_beginning;

	while (temp != NULL) {
		printf("ID: %d\n", temp->coord_id);
		printf("x: %f\n", temp->x);
		printf("y: %f\n", temp->y);
		temp = temp->next;
	}
}

void backward_display(Coordinate *list_end){
	Coordinate* temp = list_end;

	while (temp != NULL) {
		printf("ID: %d\n", temp->coord_id);
		printf("x: %f\n", temp->x);
		printf("y: %f\n", temp->y);
		temp = temp->previous;
	}
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete){
	Coordinate* temp = list_beginning;

	while (temp != NULL && temp->coord_id != coord_id_to_delete) {
		temp = temp->next;
	}
	if (temp == NULL) {
		return;
	}
	if (temp->next != NULL) {
			temp->next->previous = temp->previous;
	}
	if (temp->previous = NULL) {
			temp->previous->next = temp->next;
	}
	if (temp == list_beginning) {
		list_beginning = temp->next;
	}
	

	delete temp;
}

int list_length(Coordinate *list_beginning){
	Coordinate* temp = list_beginning;
	int length = 0;

	while (temp != NULL) {
		length++;
			temp = temp->next;
	}

	return length;
}

void closest_to(Coordinate *list_beginning, float x, float y){
	if (list_beginning == NULL) {
		return;
	}

	Coordinate* close = list_beginning;
	Coordinate* temp = list_beginning->next;
	float min = sqrt(pow(list_beginning->x - x, 2) + pow(list_beginning->y - y, 2));

	while (temp != NULL) {
		float distance = sqrt(pow(temp->x - x, 2) + pow(temp->y - y, 2));
		if (distance < min) {
			close = temp;
			min = distance;
		}
	}
	printf("ID of Closest Coordinate: %d\n", close->coord_id);
	printf("X: %f\n", close->x);
	printf("Y: %f\n", close->y);
}

int main (int argc, char* argv[]) {
	if (argc != 2) {
		printf("Coordinate Pair Number Not Entered Properly.\n");
	}

	int coordnum = atoi(argv[1]);

	Coordinate* list_beginning = NULL;
	Coordinate* list_end = NULL;

	srand(time(NULL));

	list_beginning = (Coordinate*)malloc(sizeof(Coordinate));
	list_end = list_beginning; list_end->previous = NULL;

	float x = (float)rand() / (float)RAND_MAX * 100.0;
	float y = (float)rand() / (float)RAND_MAX * 100.0;
	list_beginning = (Coordinate*)malloc(sizeof(Coordinate));
	list_beginning->x = x;
	list_beginning->y = y;
	list_beginning->coord_id = 1;
	list_beginning->next = NULL;
	list_beginning->previous = NULL;
	list_end = list_beginning;

	for (int i = 1; i < coordnum; ++i) {
		x = (float)rand() / (float)RAND_MAX * 100.0;
		y = (float)rand() / (float)RAND_MAX * 100.0;
		add_coordinate(list_end, x, y);
		list_end = list_end->next;
	}

	printf("Forward Display:\n");
	forward_display(list_beginning);

	printf("\nBackward Display:\n");
	backward_display(list_end);

	printf("\nList Length:\n");
	list_length(list_beginning);

	printf("\nDeleting Coordinate (ID: 4)...\n");
	delete_coordinate(list_beginning, 4);
	printf("\nForward Display:\n");
	forward_display(list_beginning);

	printf("\nClosest Coordinate to (8, 8):\n");
	closest_to(list_beginning, 8.0, 8.0);

	while (list_beginning != NULL) { 
		Coordinate* temp = list_beginning;
		list_beginning = list_beginning->next;
		free(temp);
	}

  return 0;
}
