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

labyrinth* deserialize (const char * const lab){
    labyrinth* l= (labyrinth*)calloc(sizeof(labyrinth), 1);
    size_t k = 0, s = 0, i;
    char j = 1;
    for (i = 0; lab[i]!=0; i++) { 
        if (lab[i]==':') k++;
        if (j) {
            if ((lab[i] != 0) && (lab[i] != ':')) s++;
            else j = 0;  
        }
    }
    l->height = k;
    l->width = s/2;
    k = 0;
    for (i = 0; lab[i]!=0; i++) {
        unsigned char prev = lab[i-1], curr = lab[i];
        if ((curr == ' ') && ((prev == '|') || (prev == '&') || (i == 0) || (prev == ':'))) { 
            list_add_back(&l->rooms, 1, 1, 0); 
        }
        else if ((curr == '_') && ((prev == '|') || (prev == '&') || (i == 0) || (prev == ':'))) {
            list_add_back(&l->rooms, 1, 0, 0); 
        }
        if ((curr == '&') && ((prev == '_') || (prev == ' '))) { 
            get_last_elem(l->rooms)->r = 1;
            k++; 
        }
        else if ((curr == '|') && ((prev == '_') || (prev == ' '))) { 
            get_last_elem(l->rooms)->r = 0;
            k++; 
        }
    }
    return l;
}

char* serialize (const labyrinth* const lab){
    char* buf = (char*) calloc(1024, 1);
    size_t i, j;
    for (i = 0; i< lab->height; ++i){ 
    point_t* cur = list_point_at(lab->rooms, i*lab->width);
        for(j = 0; j < lab->width; j++, cur = cur->next){
            if (cur->b) { 
                if (cur->is_way) strcat(buf, "&");
                else strcat(buf, " "); 
            }
            else if (cur->is_way) strcat(buf, "\033[4m&\033[24m");
                else strcat(buf, "_");
            if (cur->r) strcat(buf, " "); else strcat(buf, "|");
        }
        strcat(buf, "\n");
    }
    for (i = 0; buf[i]!=0; i++) if (buf[i]==-37) buf[i]=' ';
    return buf;
}
