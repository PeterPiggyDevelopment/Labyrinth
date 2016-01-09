/*
 * =====================================================================================
 *
 *       Filename:  serialization.c
 *
 *    Description:  Serializes and Deserializes labyrinth
 *
 *        Version:  1.0
 *        Created:  12/22/2015 09:19:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kirill Yartsev 
 *   Organization:  IFMO UNIVERSITY
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include "../include/list_funcs.h"
#include "../include/serialization.h"

labyrinth* deserialize (char* lab){
    labyrinth* l= (labyrinth*)malloc(sizeof(labyrinth));
    size_t k = 0, s = 0, i;
    char j = 1;
    for (i = 0; lab[i]!=0; i++) { 
        if (lab[i]=='\n') k++;
        if (j) {
            if ((lab[i] != 0) && (lab[i] != '\n')) s++;
            else j = 0;  
        }
    }
    l->height = k;
    l->width = s;
    l->rooms = (point_t*) calloc(l->width*l->height, 1);
    k = 0;
    for (i = 0; lab[i]!=0; i++) {
        unsigned char prev = lab[i-1], curr = lab[i];
        if ((curr == ' ') && ((prev == '|') || (prev == 249)))  l->rooms[k].b = 1;
        else if ((curr == '_') && ((prev == '|') || (prev == 249))) l->rooms[k].b = 0;
        if ((curr == ' ') && ((prev == '_') || (prev == ' '))) { l->rooms[k].r = 1; k++; }
        else if ((curr == '|') && ((prev == '_') || (prev == ' '))) { l->rooms[k].r = 0; k++; }
    }
    return l;
}

char* serialize (labyrinth* lab){
	char* buf = (char*) calloc(1024, 1);
    size_t i;
    for (i = 0; i< lab->height; i++){ 
        point_t* row = (lab->rooms+i*lab->width);
        char w[2] = {-37, 0};
        for(; row; row = row->next){
            if (row->b) { 
                if (row->is_way) strcat(buf, w);
                else { 
                    if (!row->b) strcat(buf, "_");
                    else strcat(buf, " "); 
                }
            }
            if (row->r) strcat(buf, " "); else strcat(buf, "|");
        }
        strcat(buf, "\n");
    }
	return buf;
}
