#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_key.h"
#include "ctuix_tree.h"
#include "ctuix_utils.h"

void ctuix_key_handler_root(CTUIX_Manager *ctuix_manager)
{
    ctuix_manager->ch = wgetch(ctuix_manager->active_node->window);
    if(ctuix_manager->ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_manager->active_node;
        ctuix_manager->active_node = ctuix_select_next_window(ctuix_manager->active_node);
        ctuix_update_selection(current_active, ctuix_manager->active_node);
    }
}

void ctuix_key_handler_panel(CTUIX_Manager *ctuix_manager)
{
    ctuix_manager->ch = wgetch(ctuix_manager->active_node->window);
    if(ctuix_manager->ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_manager->active_node;
        ctuix_manager->active_node = ctuix_select_next_window(ctuix_manager->active_node);
        ctuix_update_selection(current_active, ctuix_manager->active_node);
    }
}

void ctuix_key_handler_selection_box(CTUIX_Manager *ctuix_manager)
{
    ctuix_manager->ch = wgetch(ctuix_manager->active_node->window);
    if(ctuix_manager->ch == KEY_RIGHT)
    {
        ctuix_select_next_item(ctuix_manager->active_node);
    }
    else if(ctuix_manager->ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_manager->active_node;
        ctuix_manager->active_node = ctuix_select_next_window(ctuix_manager->active_node);
        ctuix_update_selection(current_active, ctuix_manager->active_node);
    }
}

void ctuix_key_handler_button(CTUIX_Manager *ctuix_manager)
{
    ctuix_manager->ch = wgetch(ctuix_manager->active_node->window);
    if(ctuix_manager->ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_manager->active_node;
        ctuix_manager->active_node = ctuix_select_next_window(ctuix_manager->active_node);
        ctuix_update_selection(current_active, ctuix_manager->active_node);
    }
}
