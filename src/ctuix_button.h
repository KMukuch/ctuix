#ifndef CTUIX_BUTTON_H
#define CTUIX_BUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

typedef struct CTUIX_Button
{
    CTUIX_Node base_node;

    char* value;

    void (*event_holder)(void);

} CTUIX_Button;

CTUIX_Button* ctuix_button_create();

CTUIX_Node* ctuix_button_key_handler(CTUIX_Node *ctuix_node);

void ctuix_button_draw(CTUIX_Node *ctuix_node);

void ctuix_button_set_value(CTUIX_Node *ctuix_node, char* value);

void ctuix_button_set_event_handler(CTUIX_Manager *ctuix_manager, char *ctuix_node_id, void (*event_handler)(void));

#endif