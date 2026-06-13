#ifndef CTUIX_PANEL_H
#define CTUIX_PANEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_event.h"

typedef struct CTUIX_Panel
{
    CTUIX_Node base_node;

} CTUIX_Panel;

CTUIX_Panel* ctuix_panel_create();

void ctuix_key_handler_panel(CTUIX_Node *ctuix_node);

void ctuix_draw_panel(CTUIX_Node *ctuix_node);

#endif