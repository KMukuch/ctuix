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

typedef enum
{
    CTUIX_EVENT_NONE,
    CTUIX_EVENT_QUIT,
    CTUIX_EVENT_SUBMIT,
    CTUIX_EVENT_LOAD
} CTUIX_Event_Type;

typedef struct CTUIX_Event
{
    CTUIX_Event_Type ctuix_event_type;
    void *user_data;
} CTUIX_Event;

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

    void (*draw)(struct CTUIX_Node*);
    struct CTUIX_Node* (*key_handler)(struct CTUIX_Node* ctuix_node, int* ch);

    CTUIX_Event (*on_click)(struct CTUIX_Node*, void *user_data);
    CTUIX_Event node_event;

    struct CTUIX_Node *parent;
    struct CTUIX_Node *children;
    struct CTUIX_Node *next;
} CTUIX_Node;

typedef struct CTUIX_Manager
{
    CTUIX_Node* root_node;
    CTUIX_Node* active_node;
    
    CTUIX_Event* current_event;
    int event_count;
    void (*event_handler)(struct CTUIX_Manager *ctuix_manager, CTUIX_Event *ctuix_event);
    
    int ch;
} CTUIX_Manager;

CTUIX_Node* ctuix_node_create(CTUIX_Element_Type ctuix_element_type, int x, int y, int w, int h, bool focusable, bool input_enabled, char* name, char* value, char* id);
CTUIX_Manager* ctuix_manager_create(CTUIX_Node *ctuix_node);

void ctuix_node_free(CTUIX_Node *ctuix_node);

#endif