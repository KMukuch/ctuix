#ifndef CTUIX_SCROLL_PANEL_H
#define CTUIX_SCROLL_PANEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

typedef struct CTUIX_Scroll_Panel
{
    CTUIX_Node base_node;

    // meta
    int selected_index;
    int scroll_offset;
    int line_count;
    int visible;

    char* value;
    
} CTUIX_Scroll_Panel;

CTUIX_Scroll_Panel* ctuix_scroll_panel_create();

CTUIX_Node* ctuix_scroll_panel_key_handler(CTUIX_Node *ctuix_node);

void ctuix_scroll_panel_draw(CTUIX_Node *ctuix_node);

void ctuix_scroll_panel_set_value(CTUIX_Node *ctuix_node, char* value);

#endif