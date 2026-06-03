#ifndef CTUIX_SELECTION_BOX_H
#define CTUIX_SELECTION_BOX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_event.h"

typedef struct CTUIX_Selection_Box
{
    CTUIX_Node base_node;

    // meta
    int selected_index;
    int scroll_offset;
    int line_count;
    int visible;
    
} CTUIX_Selection_Box;

CTUIX_Selection_Box* ctuix_selection_box_create();

CTUIX_Node* ctuix_find_item_by_ind(CTUIX_Node *ctuix_node);

#endif