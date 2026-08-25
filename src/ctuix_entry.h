#ifndef CTUIX_ENTRY_H
#define CTUIX_ENTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

typedef struct CTUIX_Entry
{
    CTUIX_Node base_node;

    // meta
    int line_count;
    int visible;
    int length;
    int cursor_x;
    int cursor_y;

    char *value;

} CTUIX_Entry;

CTUIX_Entry* ctuix_entry_create();

CTUIX_Node* ctuix_entry_key_handler(CTUIX_Node *ctuix_node);

void ctuix_entry_draw(CTUIX_Node *ctuix_node);

char** ctuix_entry_wrap_value(CTUIX_Node *ctuix_node);

#endif