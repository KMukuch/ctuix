#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_key.h"
#include "ctuix_tree.h"
#include "ctuix_nav.h"
#include "ctuix_draw.h"

CTUIX_Node* ctuix_key_handler_root(CTUIX_Node *ctuix_node, int *ch)
{
    *ch = wgetch(ctuix_node->window);
    if(*ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        current_active->active = false;
        next_node->active = true;
        ctuix_draw_tree(next_node);

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
        current_active->active = false;
        next_node->active = true;
        ctuix_draw_tree(current_active);
        ctuix_draw_tree(next_node);
        
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
        current_active->active = false;
        next_node->active = true;
        ctuix_draw_tree(current_active);
        ctuix_draw_tree(next_node);

        return next_node;
    }
    else if(*ch == KEY_DOWN)
    {
        return ctuix_find_item_by_ind(ctuix_node);
    }

    return ctuix_node;
}

CTUIX_Node* ctuix_key_handler_item(CTUIX_Node *ctuix_node, int *ch)
{
    *ch = wgetch(ctuix_node->parent->window);
    if(*ch == KEY_UP)
    {
        if(ctuix_node->parent->selected_index > 0)
        {
            ctuix_node->parent->selected_index--;
            if(ctuix_node->parent->selected_index < ctuix_node->parent->scroll_offset)
            {
                ctuix_node->parent->scroll_offset = ctuix_node->parent->selected_index;
            }
            ctuix_draw_tree(ctuix_node->parent);  
        }
        return ctuix_find_item_by_ind(ctuix_node->parent);
    }
    else if(*ch == KEY_DOWN)
    {
        if(ctuix_node->parent->selected_index < ctuix_count_children(ctuix_node->parent) - 1)
        {
            ctuix_node->parent->selected_index++;
            if(ctuix_node->parent->selected_index >= ctuix_node->parent->scroll_offset + ctuix_node->parent->visible)
            {
                ctuix_node->parent->scroll_offset = ctuix_node->parent->selected_index - ctuix_node->parent->visible + 1;
            }
            ctuix_draw_tree(ctuix_node->parent);  
        }
        return ctuix_find_item_by_ind(ctuix_node->parent);
    }
    else if(*ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node->parent;
        CTUIX_Node *next_node = ctuix_select_next_window(current_active);
        current_active->active = false;
        next_node->active = true;
        ctuix_draw_tree(current_active);
        ctuix_draw_tree(next_node);

        return next_node;
    }

    return ctuix_node;
}

CTUIX_Node* ctuix_key_handler_scroll_panel(CTUIX_Node *ctuix_node, int *ch)
{
    *ch = wgetch(ctuix_node->window);
    if(*ch == KEY_UP)
    {
        if(ctuix_node->scroll_offset > 0)
        {
            ctuix_node->scroll_offset--;
            ctuix_draw_tree(ctuix_node);
        }
        return ctuix_node;
    }
    else if(*ch == KEY_DOWN)
    {
        if(ctuix_node->scroll_offset < ctuix_node->line_count - 1)
        {
            ctuix_node->scroll_offset++;
            ctuix_draw_tree(ctuix_node);
        }
        return ctuix_node;
    }
    else if(*ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        current_active->active = false;
        next_node->active = true;
        ctuix_draw_tree(current_active);
        ctuix_draw_tree(next_node);

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
        current_active->active = false;
        next_node->active = true;
        ctuix_draw_tree(current_active);
        ctuix_draw_tree(next_node);

        return next_node;
    }
    else if(*ch == '\n' || *ch == '\r' || *ch == KEY_ENTER)
    {
        ctuix_node->node_event = ctuix_node->on_click(ctuix_node, 0);
    }

    return ctuix_node;
}