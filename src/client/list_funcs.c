#include <malloc.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/list_funcs.h"

void list_add_front(point_t** list, const int r, const int b, const int set){
	point_t* old_list = *list;
	point_t* new_list = (point_t*)malloc(sizeof(point_t));
	new_list->r = r;
	new_list->b = b;
	new_list->is_way = 0;
	new_list->set = set;
	new_list->next = old_list;
	*list = new_list;
}

void list_add_back(point_t** list, const int r, const int b, const int set){
	if (*list) {
		point_t* prev_elem;
		point_t* elem = *list;
		while(elem) { prev_elem = elem; elem=elem->next; }
		list_add_front(&(prev_elem->next), r, b, set);
	} else list_add_front(list, r, b, set);
}

size_t list_count(const point_t* list){ 
	size_t c;
	for(c = 0; list; list = list->next, c++);
	return c;
}

point_t* list_point_at(point_t* list, const size_t index){
	size_t i;
	for (i = 0; i < index; i++)
		if (list) list = list->next;
		else return NULL;
	return list;
}

int list_get_r(point_t* const list, const size_t index, int* const err){
	point_t* elem = list_point_at(list, index);
	if (!elem){
		*err = 1;
		return 0;
	}
	return elem->r;
}

int list_get_b(point_t* const list, const size_t index, int* const err){
	point_t* elem = list_point_at(list, index);
	if (elem == 0){
		*err = 1;
		return 0;
	}
	return elem->b;
}

void list_free(point_t* list){
	while(list){
		point_t* old_elem = list;
		list = list->next;
		free(old_elem); 
	}
}

point_t* get_last_elem(point_t* list){
	while(list->next) { list=list->next; }
	return list;
}
