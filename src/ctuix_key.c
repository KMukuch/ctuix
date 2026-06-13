#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_key.h"
#include "ctuix_tree.h"
#include "ctuix_nav.h"
#include "ctuix_draw.h"

void ctuix_key_handler_root(CTUIX_Node *ctuix_node)
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
            ctuix_draw_tree(next_node);

            ctuix_node = next_node;
        }
    }
}