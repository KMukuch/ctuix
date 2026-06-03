#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_button.h"
#include "ctuix_event.h"

CTUIX_Button* ctuix_button_create()
{
    CTUIX_Button *ctuix_button = calloc(1, sizeof(CTUIX_Button));
    if(!ctuix_button)
    {
        return NULL;
    }

    // set up the base node
    ctuix_button->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_button->base_node.draw = NULL;
    ctuix_button->base_node.key_handler = NULL;

    return ctuix_button;
}