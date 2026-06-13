#ifndef CTUIX_BUTTON_H
#define CTUIX_BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_event.h"

typedef struct CTUIX_Button
{
    CTUIX_Node base_node;

    char* value;

} CTUIX_Button;

CTUIX_Button* ctuix_button_create();

void ctuix_key_handler_button(CTUIX_Node *ctuix_node);

void ctuix_draw_button(CTUIX_Node *ctuix_node);

#endif