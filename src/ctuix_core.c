#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_core.h"
#include "ctuix_tree.h"
#include "ctuix_utils.h"
#include "ctuix_root.h"

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
    if(!ctuix_manager->ctuix_scene->root_node) return 0;
    
    ctuix_draw_tree(ctuix_manager->ctuix_scene->root_node);
    refresh();

    while(ctuix_manager->ctuix_scene->active_node)
    {
        if(ctuix_manager->ctuix_scene->active_node->key_handler)
        {
            ctuix_manager->ctuix_scene->active_node = ctuix_manager->ctuix_scene->active_node->key_handler(ctuix_manager->ctuix_scene->active_node);
        }
        refresh();
    }

    return 1;
}

void ctuix_end()
{
    endwin();
}