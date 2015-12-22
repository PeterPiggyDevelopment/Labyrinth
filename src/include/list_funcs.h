#ifndef _LIST_FUNCS_H_
#define _LIST_FUNCS_H_

#include <stdio.h>

typedef unsigned long size_t;

typedef struct point_t {
	int set;
	int r;
	int b;
	struct point_t* next;
}point_t;

void list_add_front(point_t** list, int r, int b, int set);
void list_add_back(point_t** list, int r, int b, int set);
int list_get_r(point_t* list, size_t index, int* err);
int list_get_b(point_t* list, size_t index, int* err);
void list_free(point_t* list);
size_t list_count(point_t* list);
point_t* list_point_at(point_t* list, size_t index);
#endif
