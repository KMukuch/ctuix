#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_core.h"
#include "ctuix_tree.h"
#include "ctuix_utils.h"
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

    while(ctuix_manager->ch != 'q')
    {
        if(ctuix_manager->active_node->key_handler)
        {
            ctuix_manager->active_node = ctuix_manager->active_node->key_handler(ctuix_manager->active_node, &ctuix_manager->ch);

            if(ctuix_manager->active_node->node_event.ctuix_event_type == CTUIX_EVENT_LOAD)
            {
                CTUIX_Manager *ctuix_manager_new = ctuix_find_manager_by_path(ctuix_manager, ctuix_manager->active_node->node_event.user_data);
                if(ctuix_manager_new)
                {
                    ctuix_manager_new->ch = 0;
                    ctuix_run(ctuix_manager_new);
                    ctuix_draw_tree(ctuix_manager->root_node);
                }
                ctuix_manager->active_node->node_event.ctuix_event_type = CTUIX_EVENT_NONE;
            }
        }
        refresh();
    }

    return 1;
}

void ctuix_end()
{
    endwin();
}