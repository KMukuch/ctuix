#ifndef CTUIX_WIDGET_H
#define CTUIX_WIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

typedef enum {
    CTUIX_TREE_ELEMENT_ROOT,
    CTUIX_TREE_ELEMENT_PANEL,
    CTUIX_TREE_ELEMENT_SELECTION_BOX,
    CTUIX_TREE_ELEMENT_SCROLL_PANEL,
    CTUIX_TREE_ELEMENT_LABEL,
    CTUIX_TREE_ELEMENT_BUTTON,
    CTUIX_TREE_ELEMENT_ENTRY
} CTUIX_Element_Type;

typedef struct CTUIX_Node {
    CTUIX_Element_Type ctuix_element_type;
    int x, y, w, h;
    bool user_input;
    bool active;

    struct CTUIX_Widget *parent;
    struct CTUIX_Widget *children;
    struct CTUIX_Widget *next;

    void (*draw)(struct CTUIX_Node *ctuix_node, WINDOW *window);
    void (*handle_key)(struct CTUIX_Node *ctuix_node, int key);
} CTUIX_Node;

CTUIX_Node ctuix_node_create(CTUIX_Element_Type ctuix_element_type, int x, int y, int w, int h, bool user_input);
CTUIX_Node ctuix_node_delete(CTUIX_Node *ctuix_tree, CTUIX_Node *ctuix_node);

#endif
