#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_core.h"
#include "ctuix_tree.h"
#include "ctuix_utils.h"
#include "ctuix_manager.h"
#include "ctuix_draw.h"
#include "ctuix_key.h"

void ctuix_init()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
}

int ctuix_run(CTUIX_Manager *ctuix_manager)
{
    if(!ctuix_manager->root_node) return 0;
    
    ctuix_draw_tree(ctuix_manager->root_node);
    refresh();
    
    ctuix_manager->ch = ctuix_key_listener(ctuix_manager->active_node);

    while(ctuix_manager->ch != 'q')
    {
        CTUIX_Node *current_active = ctuix_manager->active_node;
        ctuix_manager->active_node = ctuix_select_next(ctuix_manager->active_node);
        ctuix_update_selection(current_active, ctuix_manager->active_node);
        
        refresh();

        ctuix_manager->ch = ctuix_key_listener(ctuix_manager->active_node);
    }

    return 1;
}

void ctuix_end()
{
    endwin();
}