/*
 * =====================================================================================
 *
 *       Filename:  find_way.c
 *
 *    Description:  Finds way in the labyrinth.
 *
 *        Version:  1.0
 *        Created:  12/22/2015 09:08:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  IFMO UNIVERSITY
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "../include/list_funcs.h"
#include "../include/serialization.h"

typedef enum {
    BOTTOM=0, 
    RIGHT=1, 
    LEFT=2, 
    TOP=3
} side;

labyrinth* lab;

point_t* get_room(int x, int y){
    return lab->rooms + (y*lab->width+x);
}

char is_way(int x, int y, char side){
    switch(side){
        case BOTTOM:return get_room(x,y)->b;
        case RIGHT:return get_room(x,y)->r;
        case LEFT:return get_room(x-1,y)->r;
        case TOP:return get_room(x,y-1)->b;
        default:return 0;
    }
}

char find_way(int bX, int bY, int eX, int eY, int lway){
    char result = 0;
    if ((bX == eX)&&(bY == eY)) return 1;
    else { }
    return result;
}

char start_finding(char* l){
    char is_way;
    lab = deserialize(l);
    is_way = find_way(2,4,2,5,0);
    /* return serialize(way); */
    return is_way;
}
