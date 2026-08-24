#ifndef CTUIX_PANEL_H
#define CTUIX_PANEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

typedef struct CTUIX_Panel
{
    CTUIX_Node base_node;

} CTUIX_Panel;

CTUIX_Panel* ctuix_panel_create();

CTUIX_Node* ctuix_panel_key_handler(CTUIX_Node *ctuix_node);

void ctuix_panel_draw(CTUIX_Node *ctuix_node);

#endif