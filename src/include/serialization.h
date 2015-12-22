/*
 * =====================================================================================
 *
 *       Filename:  serialization.h
 *
 *    Description:  Serialization header
 *
 *        Version:  1.0
 *        Created:  12/22/2015 09:23:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  IFMO UNIVERSITY
 *
 * =====================================================================================
 */

#ifndef _SERIALIZE_
#define _SERIALIZE_
#include "list_funcs.h"

char* serialize (point* way);
char* deserialize (char* lab);
#endif
