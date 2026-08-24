#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_label.h"
#include "ctuix_root.h"
#include "ctuix_nav.h"

CTUIX_Label* ctuix_label_create()
{
    CTUIX_Label *ctuix_label = calloc(1, sizeof(CTUIX_Label));
    if(!ctuix_label)
    {
        return NULL;
    }

    // set up the base node
    ctuix_label->base_node.ctuix_element_type = CTUIX_ELEMENT_LABEL;
    ctuix_label->base_node.draw = NULL;
    ctuix_label->base_node.key_handler = NULL;

    return ctuix_label;
}

void ctuix_label_draw(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    CTUIX_Label *ctuix_label = (CTUIX_Label*)ctuix_node;

    if(!ctuix_node->window)
    {
        int max_y, max_x;
        getmaxyx(ctuix_node->parent->window, max_y, max_x);
        if(ctuix_node->ctuix_element_x_alignment == CTUIX_ELEMENT_X_ALIGNMENT_CENTER)
        {
            ctuix_node->x = (max_x - strlen(ctuix_label->value)) / 2;
        }
        if(ctuix_node->ctuix_element_y_alignment == CTUIX_ELEMENT_Y_ALIGNMENT_CENTER)
        {
            ctuix_node->y = (max_y - ctuix_node->h) / 2;
        }

        ctuix_node->window = derwin(ctuix_node->parent->window, 1, strlen(ctuix_label->value), ctuix_node->y, ctuix_node->x);
    }
    
    if(ctuix_node->parent->window)
    {
        mvwprintw(ctuix_node->window, 0, 0, "%s", ctuix_label->value);
        wrefresh(ctuix_node->window);
    }
}

void ctuix_label_set_value(CTUIX_Node *ctuix_node, char* value)
{
    if(!ctuix_node) return;
    if(ctuix_node->ctuix_element_type != CTUIX_ELEMENT_LABEL) return;
    if(!value) return;

    CTUIX_Label *ctuix_label = (CTUIX_Label*)ctuix_node;
    ctuix_label->value = strdup(value);
}