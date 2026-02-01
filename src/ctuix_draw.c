#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_draw.h"

void ctuix_node_draw_default(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if (!ctuix_node->window)
    {
        ctuix_node->window = newwin(ctuix_node->h, ctuix_node->w, ctuix_node->y, ctuix_node->x);
        keypad(ctuix_node->window, TRUE);
    }
    werase(ctuix_node->window);
    box(ctuix_node->window, 0, 0);
    mvwprintw(ctuix_node->window, 0, 1, "-");
}

void ctuix_tree_draw(CTUIX_Node *ctuix_node)
{
    if (!ctuix_node) return;
    
    if(ctuix_node->draw)
    {
        ctuix_node->draw(ctuix_node);
    }
    
    CTUIX_Node *ctuix_node_child = ctuix_node->children;
    while(ctuix_node_child) {
        ctuix_tree_draw(ctuix_node_child);
        ctuix_node_child = ctuix_node_child->next;
    }
}