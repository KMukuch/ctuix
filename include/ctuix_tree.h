#ifndef CTUIX_TREE_H
#define CTUIX_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

#define MAX_LINE 50

typedef enum
{
    CTUIX_ELEMENT_ERROR,
    CTUIX_ELEMENT_ROOT,
    CTUIX_ELEMENT_PANEL,
    CTUIX_ELEMENT_SELECTION_BOX,
    CTUIX_ELEMENT_SCROLL_PANEL,
    CTUIX_ELEMENT_LABEL,
    CTUIX_ELEMENT_BUTTON,
    CTUIX_ELEMENT_ENTRY
} CTUIX_Element_Type;

typedef struct CTUIX_Node
{
    WINDOW* window;

    CTUIX_Element_Type ctuix_element_type;
    int x, y, w, h;
    bool user_input_enabled;
    bool active;

    struct CTUIX_Node *parent;
    struct CTUIX_Node *children;
    struct CTUIX_Node *next;
} CTUIX_Node;

CTUIX_Node* ctuix_node_create(CTUIX_Element_Type ctuix_element_type, int x, int y, int w, int h, bool user_input_enabled);

CTUIX_Node* ctuix_node_get_next_focusable(CTUIX_Node *ctuix_node);
CTUIX_Node* ctuix_node_get_prev_focusable(CTUIX_Node *ctuix_node);

void ctuix_node_free(CTUIX_Node *ctuix_node);

#endif