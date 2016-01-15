#ifndef _LIST_FUNCS_H_
#define _LIST_FUNCS_H_

#include <stdio.h>

typedef unsigned long size_t;

typedef struct point_t {
    int set;
    int is_way;
    int r;
    int b;
    struct point_t* next;
} point_t;

typedef struct labyrinth {
    point_t* rooms;
    size_t width;
    size_t height;
} labyrinth;

void list_add_front(point_t** list, const int r, const int b, const int set);
void list_add_back(point_t** list, const int r, const int b, const int set);
int list_get_r(point_t* const list, const size_t index, int* const err);
int list_get_b(point_t* const list, const size_t index, int* const err);
void list_free(point_t* list);
size_t list_count(const point_t* list);
point_t*  get_last_elem(point_t* list);
point_t* list_point_at(point_t* list, const size_t index);
#endif
