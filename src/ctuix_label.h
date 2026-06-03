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

#endif