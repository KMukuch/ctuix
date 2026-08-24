#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_panel.h"
#include "ctuix_root.h"
#include "ctuix_nav.h"

CTUIX_Panel* ctuix_panel_create()
{
    CTUIX_Panel *ctuix_panel = calloc(1, sizeof(CTUIX_Panel));
    if(!ctuix_panel)
    {
        return NULL;
    }

    // set up the base node
    ctuix_panel->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_panel->base_node.draw = NULL;
    ctuix_panel->base_node.key_handler = NULL;

    return ctuix_panel;
}

CTUIX_Node* ctuix_panel_key_handler(CTUIX_Node *ctuix_node)
{
    int ch = wgetch(ctuix_node->window);
    if(ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        if(next_node)
        {
            current_active->active = false;
            next_node->active = true;
            ctuix_draw_tree(current_active);
            ctuix_draw_tree(next_node);
            
            return next_node;
        }
    }
    else if(ch == 'q')
    {
        return NULL;
    }

    return ctuix_node;
}

void ctuix_panel_draw(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if(!ctuix_node->window)
    {
        int max_y, max_x;
        getmaxyx(ctuix_node->parent->window, max_y, max_x);

        if(ctuix_node->ctuix_element_w_units == CTUIX_ELEMENT_UNITS_VW)
        {
            int vw = max_x * ctuix_node->w / 100;
            ctuix_node->w = vw;
        }
        if(ctuix_node->ctuix_element_h_units == CTUIX_ELEMENT_UNITS_VH)
        {
            int vh = max_y * ctuix_node->h / 100;
            ctuix_node->h = vh;
        }
        
        if(ctuix_node->ctuix_element_x_alignment == CTUIX_ELEMENT_X_ALIGNMENT_CENTER)
        {
            ctuix_node->x = (max_x - ctuix_node->w) / 2;
        }
        if(ctuix_node->ctuix_element_y_alignment == CTUIX_ELEMENT_Y_ALIGNMENT_CENTER)
        {
            ctuix_node->y = (max_y - ctuix_node->h) / 2;
        }
            
        ctuix_node->window = derwin(ctuix_node->parent->window, ctuix_node->h, ctuix_node->w, ctuix_node->y, ctuix_node->x);
    }
    
    if(ctuix_node->window)
    {
        keypad(ctuix_node->window, TRUE);
        werase(ctuix_node->window);
        if(ctuix_node->active)
        {
            wattron(ctuix_node->window, A_REVERSE);
            box(ctuix_node->window, 0, 0);
            wattroff(ctuix_node->window, A_REVERSE);
        }
        else
        {
            wattroff(ctuix_node->window, A_REVERSE);
            box(ctuix_node->window, 0, 0);
        }
        if(ctuix_node->name)
        {
            mvwprintw(ctuix_node->window, 0, 1, "%s", ctuix_node->name);
        }
        wrefresh(ctuix_node->window);
    }
}