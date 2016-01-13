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
#include <string.h>
#include "../include/list_funcs.h"
#include "../include/serialization.h"

labyrinth* lab;

typedef enum {
    BOTTOM=0, 
    RIGHT=1, 
    LEFT=2, 
    TOP=3
} side;

static point_t* get_room(int x, int y){
    return list_point_at(lab->rooms, y*lab->width+x);
}

static char is_way(int x, int y, char side){
    switch(side){
        case BOTTOM:return get_room(x,y)->b;
        case RIGHT:return get_room(x,y)->r;
        case LEFT:return get_room(x-1,y)->r;
        case TOP:return get_room(x,y-1)->b;
        default:return 0;
    }
}

static char find_way(int bX, int bY, int eX, int eY, int lway){
    char result = 0;
    if ((bX == eX)&&(bY == eY)) { 
        get_room(bX, bY)->is_way = 1;
        return 1;
    }
    else {
        if (is_way(bX, bY, LEFT) && (get_room(bX - 1, bY )->set == 0)){
            get_room(bX-1, bY)->set = lway+1;
            result = find_way(bX-1, bY, eX, eY, lway+1);
        }
        if (result) { 
            get_room(bX, bY)->is_way = 1;
            return 1; 
        }
        if (is_way(bX, bY, RIGHT) && (get_room(bX + 1, bY )->set == 0)){
            get_room(bX+1, bY)->set = lway+1;
            result = find_way(bX+1, bY, eX, eY, lway+1);
        }
        if (result) { 
            get_room(bX, bY)->is_way = 1;
            return 1; 
        }
        if (is_way(bX, bY, TOP) && (get_room(bX, bY-1)->set == 0)){
            get_room(bX, bY-1)->set = lway+1;
            result = find_way(bX, bY-1, eX, eY, lway+1);
        }
        if (result) { 
            get_room(bX, bY)->is_way = 1;
            return 1; 
        }
        if (is_way(bX, bY, BOTTOM) && (get_room(bX, bY+1)->set == 0)){
            get_room(bX, bY+1)->set = lway+1;
            result = find_way(bX, bY+1, eX, eY, lway+1);
        }
        if (result) { 
            get_room(bX, bY)->is_way = 1;
            return 1; 
        }
    }
    if (!result) get_room(bX, bY)->set = lab->width * lab->height;
    return 0;
}  

char* start_finding(char* l){
    int bX=1, bY=1, eX=10, eY=10;
    char is_way=0;
    lab = deserialize(l);
    is_way =   find_way(bX,bY,eX,eY,0);
    if (is_way) return serialize(lab);
    else {
        char* buf = serialize(lab),* buf2 = calloc(2000, 1);
        memcpy(buf2, buf, strlen(buf)/2-5);
        strcat(buf2, "!!NO WAY!!");
        memcpy(buf2 + (strlen(buf)/2+5), buf+(strlen(buf)/2+5), strlen(buf)/2);
        return buf2;
    }
}
