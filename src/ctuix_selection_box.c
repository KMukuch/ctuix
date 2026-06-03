#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_selection_box.h"
#include "ctuix_utils.h"

CTUIX_Selection_Box* ctuix_selection_box_create()
{
    CTUIX_Selection_Box *ctuix_selection_box = calloc(1, sizeof(CTUIX_Selection_Box));
    if(!ctuix_selection_box)
    {
        return NULL;
    }

    // set up the base node
    ctuix_selection_box->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_selection_box->base_node.draw = NULL;
    ctuix_selection_box->base_node.key_handler = NULL;

    return ctuix_selection_box;
}

CTUIX_Node* ctuix_find_item_by_ind(CTUIX_Node *ctuix_node)
{
    
}