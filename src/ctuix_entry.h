#ifndef CTUIX_ENTRY_H
#define CTUIX_ENTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_event.h"

typedef struct CTUIX_Entry
{
    CTUIX_Node base_node;

    // meta
    char buffer[MAX_ENTRY];
    int cursor_x;
    
} CTUIX_Entry;

CTUIX_Entry* ctuix_entry_create();

#endif