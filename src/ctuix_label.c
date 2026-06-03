#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_label.h"
#include "ctuix_event.h"

CTUIX_Label* ctuix_label_create()
{
    CTUIX_Label *ctuix_label = calloc(1, sizeof(CTUIX_Label));
    if(!ctuix_label)
    {
        return NULL;
    }

    // set up the base node
    ctuix_label->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_label->base_node.draw = NULL;
    ctuix_label->base_node.key_handler = NULL;

    return ctuix_label;
}