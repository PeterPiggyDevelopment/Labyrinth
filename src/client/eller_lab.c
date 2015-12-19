#include "eller_lab.h"
#include "list_funcs.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

int rand_int(int n) {
	if ((n - 1) == RAND_MAX) {
		return rand();
	} else {
		long end = RAND_MAX / n;
		int r;
		assert (end > 0L);
		end *= n;
		while ((r = rand()) >= end);
		return r % n;
	}
}

/*
 * saves our row in buffer
 */
char* print(point_t* row){
	char* buf = (char*) calloc(128, 1);
	for(; row; row = row->next){
		if (row->b) strcat(buf, " "); else strcat(buf, "_");
		if (row->r) strcat(buf, " "); else strcat(buf, "|");
	}
	strcat(buf, "\n");
	return buf;
}

/*
 * creates row of the labyrinth wich we'll modify
 */
point_t* create_row(int n){
	int i;
	point_t* new_row = NULL;
	for (i = 0; i < n; i++)
		list_add_front(&new_row, 1, 1, 0);
	return new_row;
}

/*
 * sets bottom borders so that each set would have 
 * at least one point without border
 *
 */
void set_bottom_borders(point_t* row){ 
	int i, j, k = 0, n = list_count(row);
	point_t* s = list_point_at(row, 0);
	for (i = 0; i < n; i++){
		point_t* cur = list_point_at(row, i);
		if (cur->set == s->set) {
			if(rand_int(10)<=5){ cur->b = 0; k++; }
			j++;
		} else {
			if (j >= k) list_point_at(row, i-1)->b = 1;
			j = 0; k = 0;
			s = cur;
			i--;
		}
		if (i == n-1 && j == k) { cur->b = 1; }
	}
}

/*
 * relying on sets of points 
 * pseudo-randomly sets borders between points
 */
void set_right_borders(point_t* row){
	int i, n = list_count(row);
	for (i = 0; i < n-1; i++){
		point_t* cur = list_point_at(row, i), *next = list_point_at(row, i+1);
		if (rand_int(10)<=5) cur->r = 0;
		if (cur->r && cur->set == next->set) cur->r = 0; /*getting rid of looping*/
		if (cur->r) next->set = cur->set;
	}
}

/*
 * clean up new string
 */
void clean_up(point_t* row){
	int i, n = list_count(row);
	for (i = 0; i < n; i++){
		point_t* s = list_point_at(row, i);
		s->r = 1;
		if (!s->b) { s->set = 0; s->b = 1; }
		if (i >= n-1) s->r = 0;
	}
}


/*
 * sets uniq sets of points
 */
void set_sets(point_t* row){
	int i, n = list_count(row);
	point_t* h;
	h = list_point_at(row, 0);
	/*initial first set value*/
	if (!h->set) { 
		if (list_point_at(row, 1)->set == 1) { h->set = 2; } 
		else { h->set = 1; }
	}
	/*set sets for the rest of row*/
	for (i = 1; i < n; i++){ 
		int g;
		point_t* cur = list_point_at(row, i);
		g = list_point_at(row, i - 1)->set + 1;
		if (!cur->set) { 
			if ( i+1 < n && g != list_point_at(row, i+1)->set) cur->set = g; 
			else if (i+1 < n) cur->set = list_point_at(row, i+1)->set + 1;
			else cur->set = g;
		}
	}
}

/*
 * sets bottom borders of the last labytinth row 
 */
void set_bottom_wall(point_t* row){
	int i, n = list_count(row);
	for (i = 0; i < n; i++){ list_point_at(row, i)->b = 0; }
}

void end_up_lab(point_t* row){
	int i, n = list_count(row);
	set_bottom_wall(row);
	for (i = 0; i < n-1; i++){
		point_t* s = list_point_at(row, i),* rs = list_point_at(row, i+1);
		if (s->set != rs->set) {
			s->r = 1; 
			rs->set = s->set;
		}
	}
}

/*
 * generates next row and prints it for us without saving
 */
char* generate_row(point_t* row, int m, int k){
	clean_up(row);
	set_sets(row);
	set_right_borders(row);
	set_bottom_borders(row);
	if (k == m-1) end_up_lab(row);
	list_add_front(&row, 0, 1, 0);
	return print(row);
}

/*
 * generates fictive row. 
 * Its purpose is to create top wall
 */
char* generate_fictive_row(point_t* row){
	set_bottom_wall(row);
	row->b = 1;
	return print(row);
}

char* create_labyrinth(int n, int m){
	int i;
	char* str_lab = (char*)malloc(1024);
	point_t* row = create_row(n);
	srand((unsigned)time(NULL));
	strcpy(str_lab, generate_fictive_row(create_row(n+1)));
	for (i = 0; i < m; i++) {
		void* gen = generate_row(row, m, i);
		strcat(str_lab, gen);
		free(gen);
	}
	return str_lab;
}
