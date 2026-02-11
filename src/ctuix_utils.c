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

int ctuix_run(CTUIX_Manager *ctuix_manager)
{
    if(!ctuix_manager->root_node) return -1;
    
    ctuix_tree_draw(ctuix_manager->root_node);
    refresh();
    
    getch();

    return 0;
}

void ctuix_end()
{
    endwin();
}