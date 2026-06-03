#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_scroll_panel.h"
#include "ctuix_utils.h"

CTUIX_Scroll_Panel* ctuix_scroll_panel_create()
{
    CTUIX_Scroll_Panel *ctuix_scroll_panel = calloc(1, sizeof(CTUIX_Scroll_Panel));
    if(!ctuix_scroll_panel)
    {
        return NULL;
    }

    // set up the base node
    ctuix_scroll_panel->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_scroll_panel->base_node.draw = NULL;
    ctuix_scroll_panel->base_node.key_handler = NULL;

    return ctuix_scroll_panel;
}

CTUIX_Item* ctuix_item_create()
{
    CTUIX_Item *ctuix_item = calloc(1, sizeof(CTUIX_Item));
    if(!ctuix_item)
    {
        return NULL;
    }

    // set up the base node
    ctuix_item->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_item->base_node.draw = NULL;
    ctuix_item->base_node.key_handler = NULL;

    return ctuix_item;
}