#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_utils.h"
#include "ctuix_draw.h"

void ctuix_init()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

int ctuix_run(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return -1;

    clear();
    refresh();

    ctuix_tree_draw(ctuix_node);

    refresh();

    getch();

    return 0;
}

void ctuix_end()
{
    endwin();
}