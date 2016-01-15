#ifndef _SERIALIZE_
#define _SERIALIZE_
#include "list_funcs.h"

char* serialize (const labyrinth* const way);
labyrinth* deserialize (const char* const lab);
#endif
