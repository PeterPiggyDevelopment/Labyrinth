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

point_t* rooms = NULL;

char* start_finding(char* lab){
    deserialize(rooms);

    find_way();

    serialize();
}

point_t* find_way(){

}
