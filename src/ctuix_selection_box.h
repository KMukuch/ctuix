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
    int item_count;
    int selected_index;
    int scroll_offset;
    int line_count;
    int visible;
    
} CTUIX_Selection_Box;

typedef struct CTUIX_Item
{
    CTUIX_Node base_node;

    // meta
    int index;

    char* value;
    
} CTUIX_Item;

CTUIX_Selection_Box* ctuix_selection_box_create();
CTUIX_Item* ctuix_item_create();

void ctuix_key_handler_selection_box(CTUIX_Node *ctuix_node);
void ctuix_key_handler_item(CTUIX_Node *ctuix_node);

void ctuix_draw_selection_box(CTUIX_Node *ctuix_node);
void ctuix_draw_item(CTUIX_Node *ctuix_node);

CTUIX_Node* ctuix_find_item_by_ind(CTUIX_Node *ctuix_node);

void ctuix_item_set_ind(CTUIX_Item *ctuix_item);
void ctuix_selection_box_set_item_count(CTUIX_Selection_Box *ctuix_selection_box);


#endif