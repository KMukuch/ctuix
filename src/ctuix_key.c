#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_key.h"
#include "ctuix_tree.h"
#include "ctuix_utils.h"

CTUIX_Node* ctuix_key_handler_root(CTUIX_Node *ctuix_node, int *ch)
{
    *ch = wgetch(ctuix_node->window);
    if(*ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        ctuix_update_selection(current_active, next_node);

        return next_node;
    }

    return ctuix_node;
}

CTUIX_Node* ctuix_key_handler_panel(CTUIX_Node *ctuix_node, int *ch)
{
    *ch = wgetch(ctuix_node->window);
    if(*ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        ctuix_update_selection(current_active, next_node);

        return next_node;
    }

    return ctuix_node;
}

CTUIX_Node* ctuix_key_handler_selection_box(CTUIX_Node *ctuix_node, int *ch)
{
    *ch = wgetch(ctuix_node->window);
    if(*ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        ctuix_update_selection(current_active, next_node);

        return next_node;
    }

    return ctuix_node;
}

CTUIX_Node* ctuix_key_handler_button(CTUIX_Node *ctuix_node, int *ch)
{
    *ch = wgetch(ctuix_node->window);
    if(*ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        ctuix_update_selection(current_active, next_node);

        return next_node;
    }

    return ctuix_node;
}
