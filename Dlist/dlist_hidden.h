#ifndef __DLIST_HIDDEN_H
#define __DLIST_HIDDEN_H

#include "dlist.h"

//this header file stores the functions that are "hidden".
//A user of the list only needs to know slist.h

node * makenode(int element,node *next);

#endif
