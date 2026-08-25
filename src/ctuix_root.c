#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_root.h"
#include "ctuix_nav.h"

CTUIX_Root* ctuix_root_create()
{
    CTUIX_Root *ctuix_root = calloc(1, sizeof(CTUIX_Root));
    if(!ctuix_root)
    {
        return NULL;
    }

    // set up the base node
    ctuix_root->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_root->base_node.draw = ctuix_root_draw;
    ctuix_root->base_node.key_handler = ctuix_root_key_handler;

    return ctuix_root;
}

void ctuix_root_draw(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if(!ctuix_node->window)
    {
        if(ctuix_node->parent == NULL)
        {
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);
            
            if(ctuix_node->w == 0 || ctuix_node->h == 0)
            {
                ctuix_node->w = max_x;
                ctuix_node->h = max_y;
            }
            
            ctuix_node->window = newwin(ctuix_node->h, ctuix_node->w, 0, 0);
        }
    }
    
    if(ctuix_node->window)
    {
        keypad(ctuix_node->window, TRUE);
        werase(ctuix_node->window);
        box(ctuix_node->window, 0, 0);
        wrefresh(ctuix_node->window);
    }
}

CTUIX_Node* ctuix_root_key_handler(CTUIX_Node *ctuix_node)
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
            ctuix_tree_draw(next_node);

            return next_node;
        }
    }
    else if(ch == 'q')
    {
        return NULL;
    }

    return ctuix_node;
}