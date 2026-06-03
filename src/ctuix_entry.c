#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_entry.h"
#include "ctuix_event.h"

CTUIX_Entry* ctuix_entry_create()
{
    CTUIX_Entry *ctuix_entry = calloc(1, sizeof(CTUIX_Entry));
    if(!ctuix_entry)
    {
        return NULL;
    }

    // set up the base node
    ctuix_entry->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_entry->base_node.draw = NULL;
    ctuix_entry->base_node.key_handler = NULL;

    return ctuix_entry;
}