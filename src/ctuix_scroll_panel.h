#ifndef CTUIX_SCROLL_PANEL_H
#define CTUIX_SCROLL_PANEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_event.h"

typedef struct CTUIX_Scroll_Panel
{
    CTUIX_Node base_node;

    // meta
    int selected_index;
    int scroll_offset;
    int line_count;
    int visible;
    
} CTUIX_Scroll_Panel;

typedef struct CTUIX_Item
{
    CTUIX_Node base_node;

    // meta
    int index;

    char* value;
    
} CTUIX_Item;

CTUIX_Scroll_Panel* ctuix_scroll_panel_create();
CTUIX_Item* ctuix_item_create();

#endif