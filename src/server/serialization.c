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
#include "../include/list_funcs.h"
#include "../include/serialization.h"

labyrinth* deserialize (char* lab){
    labyrinth* l= (labyrinth*)malloc(sizeof(labyrinth));

    return l;
}

char* serialize (point_t* way){
    char* buf = "";

    return buf;
}
