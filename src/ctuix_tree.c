#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

CTUIX_Node* ctuix_node_create(CTUIX_Element_Type ctuix_element_type, int x, int y, int w, int h, bool user_input_enabled)
{
    CTUIX_Node *ctuix_node = malloc(1);

    ctuix_node->ctuix_element_type = ctuix_element_type;
    ctuix_node->x = x;
    ctuix_node->y = y;
    ctuix_node->w = w;
    ctuix_node->h = h;
    ctuix_node->user_input_enabled = user_input_enabled;

    ctuix_node->parent = NULL;
    ctuix_node->children = NULL;
    ctuix_node->next = NULL;

    ctuix_node->draw = NULL;
    ctuix_node->handle_key = NULL;

    return ctuix_node;
}