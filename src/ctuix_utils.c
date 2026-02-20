#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_utils.h"
#include "ctuix_manager.h"
#include "ctuix_draw.h"

void ctuix_init()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
}

CTUIX_Node* ctuix_select_next(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return NULL;

    CTUIX_Node *current_node = ctuix_node;
    if(current_node->children)
    {
        current_node = current_node->children;
    }
    else if(current_node->next)
    {
        current_node = current_node->next;
    }

    return current_node;
}

int ctuix_key_listener(CTUIX_Node *ctuix_node)
{
    return wgetch(ctuix_node->window);
}

int ctuix_run(CTUIX_Manager *ctuix_manager)
{
    if(!ctuix_manager->root_node) return -1;
    
    ctuix_tree_draw(ctuix_manager->root_node);
    refresh();
    
    while(ctuix_key_listener(ctuix_manager->active_node) == '\t')
    {
        CTUIX_Node *current_active = ctuix_manager->active_node;
        ctuix_manager->active_node = ctuix_select_next(ctuix_manager->active_node);
        ctuix_update_selection(current_active, ctuix_manager->active_node);
        
        refresh();
    }

    return 0;
}

void ctuix_end()
{
    endwin();
}