#ifndef CTUIX_LABEL_H
#define CTUIX_LABEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_event.h"

typedef struct CTUIX_Label
{
    CTUIX_Node base_node;

    char* value;
    
} CTUIX_Label;

CTUIX_Label* ctuix_label_create();

void ctuix_draw_label(CTUIX_Node *ctuix_node);

void ctuix_label_set_value(CTUIX_Node *ctuix_node, char* value);

#endif