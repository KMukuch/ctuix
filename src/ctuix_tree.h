#ifndef CTUIX_TREE_H
#define CTUIX_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

#define MAX_ENTRY 256

/// @brief 
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

/// @brief 
typedef enum
{
    CTUIX_ELEMENT_UNITS_AUTO,
    CTUIX_ELEMENT_UNITS_VW,
    CTUIX_ELEMENT_UNITS_VH
} CTUIX_Element_Units;

/// @brief 
typedef enum
{
    CTUIX_ELEMENT_X_ALIGNMENT_AUTO,
    CTUIX_ELEMENT_X_ALIGNMENT_CENTER
} CTUIX_Element_X_Alignment;

/// @brief 
typedef enum
{
    CTUIX_ELEMENT_Y_ALIGNMENT_AUTO,
    CTUIX_ELEMENT_Y_ALIGNMENT_CENTER
} CTUIX_Element_Y_Alignment;

/// @brief Base CTUIX struct
typedef struct CTUIX_Node
{
    // tree
    struct CTUIX_Node *parent;
    struct CTUIX_Node *children;
    struct CTUIX_Node *next;

    // vtable
    void (*draw)(struct CTUIX_Node* ctuix_node);
    struct CTUIX_Node* (*key_handler)(struct CTUIX_Node* ctuix_node);

    // meta
    CTUIX_Element_Type ctuix_element_type;

    char* name;
    char* id;

    // layout
    int x;
    int y;
    int w;
    int h;
    
    CTUIX_Element_Units ctuix_element_y_units;
    CTUIX_Element_Units ctuix_element_x_units;
    CTUIX_Element_Units ctuix_element_h_units;
    CTUIX_Element_Units ctuix_element_w_units;

    CTUIX_Element_Y_Alignment ctuix_element_y_alignment;
    CTUIX_Element_X_Alignment ctuix_element_x_alignment;
    
    // flags
    bool focusable;
    bool input;
    bool active;

    // base
    WINDOW* window;

} CTUIX_Node;

/// @brief 
typedef struct CTUIX_Scene
{
    CTUIX_Node* root_node;
    CTUIX_Node* active_node;

} CTUIX_Scene;

/// @brief 
typedef struct CTUIX_Manager
{
    char* file_name;
    
    struct CTUIX_Manager *previous;
    struct CTUIX_Manager *next;

    CTUIX_Scene *ctuix_scene;

} CTUIX_Manager;

/// @brief 
/// @param ctuix_node 
/// @param ctuix_element_type 
/// @param name 
/// @param id 
void ctuix_node_set_meta(CTUIX_Node *ctuix_node, CTUIX_Element_Type ctuix_element_type, char* name, char* id);

/// @brief 
/// @param ctuix_node 
/// @param ctuix_element_x_units 
/// @param ctuix_element_y_units 
/// @param ctuix_element_w_units 
/// @param ctuix_element_h_units 
/// @param ctuix_element_x_alignment 
/// @param ctuix_element_y_alignment 
/// @param x 
/// @param y 
/// @param w 
/// @param h 

void ctuix_node_set_layout(CTUIX_Node *ctuix_node, CTUIX_Element_Units ctuix_element_x_units, CTUIX_Element_Units ctuix_element_y_units, CTUIX_Element_Units ctuix_element_w_units, CTUIX_Element_Units ctuix_element_h_units, CTUIX_Element_X_Alignment ctuix_element_x_alignment, CTUIX_Element_Y_Alignment ctuix_element_y_alignment, int x, int y, int w, int h);

/// @brief 
/// @param ctuix_node 
/// @param focusable 
/// @param input 
void ctuix_node_set_flags(CTUIX_Node *ctuix_node, bool focusable, bool input);

/// @brief 
/// @param ctuix_node 
/// @param file_path 
/// @return 
CTUIX_Manager* ctuix_manager_create(CTUIX_Node *ctuix_node, char* file_path);

/// @brief 
/// @param ctuix_node 
/// @param ctuix_node_id 
/// @return 
CTUIX_Node* ctuix_find_node_by_id(CTUIX_Node *ctuix_node, char *ctuix_node_id);

/// @brief 
/// @param ctuix_manager
/// @param file_path 
/// @return 
CTUIX_Manager* ctuix_find_manager_by_path(CTUIX_Manager *ctuix_manager, char *file_path);

/// @brief 
/// @param ctuix_node 
void ctuix_draw_tree(CTUIX_Node *ctuix_node);

/// @brief 
/// @param ctuix_node 
void ctuix_node_free(CTUIX_Node *ctuix_node);

#endif