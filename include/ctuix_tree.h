#ifndef CTUIX_TREE_H
#define CTUIX_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

typedef enum
{
    CTUIX_ELEMENT_ERROR = -1,
    CTUIX_ELEMENT_ROOT,
    CTUIX_ELEMENT_PANEL,
    CTUIX_ELEMENT_SELECTION_BOX,
    CTUIX_ELEMENT_SCROLL_PANEL,
    CTUIX_ELEMENT_ITEM,
    CTUIX_ELEMENT_LABEL,
    CTUIX_ELEMENT_BUTTON,
    CTUIX_ELEMENT_ENTRY
} CTUIX_Element_Type;

typedef struct CTUIX_Node CTUIX_Node;
typedef struct CTUIX_Manager CTUIX_Manager;

typedef struct CTUIX_Node
{
    WINDOW* window;

    CTUIX_Element_Type ctuix_element_type;
    
    int x, y;
    int w, h;

    int selected_index;
    int scroll_offset;

    bool focusable;
    bool input_enabled;

    char* name;
    char* value;
    char* id;

    void (*draw)(CTUIX_Node*);
    void (*key_handler)(CTUIX_Manager*);

    struct CTUIX_Node *parent;
    struct CTUIX_Node *children;
    struct CTUIX_Node *next;
} CTUIX_Node;

typedef struct CTUIX_Manager
{
    CTUIX_Node* root_node;
    CTUIX_Node* active_node;
    
    int ch;
} CTUIX_Manager;

CTUIX_Node* ctuix_node_create(CTUIX_Element_Type ctuix_element_type, int x, int y, int w, int h, bool focusable, bool input_enabled, char* name, char* value);

CTUIX_Manager* ctuix_manager_create(CTUIX_Node *ctuix_node);

void ctuix_node_free(CTUIX_Node *ctuix_node);

#endif