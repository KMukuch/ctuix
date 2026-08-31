#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

void ctuix_node_set_flags(CTUIX_Node *ctuix_node, bool focusable, bool input)
{
    if(!ctuix_node)
    {
        return;
    }

    ctuix_node->focusable = focusable;
    ctuix_node->input = input;
}

void ctuix_node_set_layout(CTUIX_Node *ctuix_node, CTUIX_Element_Units ctuix_element_x_units, CTUIX_Element_Units ctuix_element_y_units, CTUIX_Element_Units ctuix_element_w_units, CTUIX_Element_Units ctuix_element_h_units, CTUIX_Element_X_Alignment ctuix_element_x_alignment, CTUIX_Element_Y_Alignment ctuix_element_y_alignment, int x, int y, int w, int h)
{
    if(!ctuix_node)
    {
        return;
    }

    ctuix_node->ctuix_element_y_units = ctuix_element_y_units;
    ctuix_node->ctuix_element_x_units = ctuix_element_x_units;
    ctuix_node->ctuix_element_h_units = ctuix_element_h_units;
    ctuix_node->ctuix_element_w_units = ctuix_element_w_units;
    
    ctuix_node->ctuix_element_x_alignment = ctuix_element_x_alignment;
    ctuix_node->ctuix_element_y_alignment = ctuix_element_y_alignment;
    
    ctuix_node->x = x;
    ctuix_node->y = y;
    ctuix_node->w = w;
    ctuix_node->h = h;
}

void ctuix_node_set_meta(CTUIX_Node *ctuix_node, CTUIX_Element_Type ctuix_element_type, char* name, char* id)
{
    if(!ctuix_node)
    {
        return;
    }

    ctuix_node->ctuix_element_type = ctuix_element_type;

    if(name)
    {
        ctuix_node->name = strdup(name);
    }
    else
    {
        ctuix_node->name = NULL;
    }

    if(id)
    {
        ctuix_node->id = strdup(id);
    }
    else
    {
        ctuix_node->id = NULL;
    }
}

CTUIX_Manager* ctuix_manager_create(CTUIX_Node *root_node, char *file_path)
{
    CTUIX_Manager *ctuix_manager = calloc(1, sizeof(CTUIX_Manager));

    ctuix_manager->file_name = strdup(file_path);

    ctuix_manager->ctuix_scene = calloc(1, sizeof(CTUIX_Scene));
    if (!ctuix_manager->ctuix_scene) {
        free(ctuix_manager->file_name);
        free(ctuix_manager);
        
        return NULL;
    }
    ctuix_manager->ctuix_scene->root_node = root_node;
    ctuix_manager->ctuix_scene->active_node = root_node; 

    ctuix_manager->previous = NULL;
    ctuix_manager->next = NULL;

    return ctuix_manager;
}

CTUIX_Node* ctuix_find_node_by_id(CTUIX_Node *ctuix_node, char *ctuix_node_id)
{
    if (!ctuix_node || !ctuix_node_id) return NULL;
    
    if (ctuix_node->id && strcmp(ctuix_node->id, ctuix_node_id) == 0)
    {
        return ctuix_node;
    }
    
    CTUIX_Node *child = ctuix_node->children;
    while (child)
    {
        CTUIX_Node *found = ctuix_find_node_by_id(child, ctuix_node_id);
        if(found) 
        {
            return found;
        }
        else
        {
            child = child->next;
        }
    }
    
    return NULL;
}

CTUIX_Manager* ctuix_find_manager_by_path(CTUIX_Manager *ctuix_manager, char *file_path)
{
    CTUIX_Manager *current_manager = ctuix_manager;
    while(current_manager)
    {
        if(current_manager->file_name && strcmp(current_manager->file_name, file_path) == 0)
        {
            return current_manager;
        }
        current_manager = current_manager->next;
    }

    return NULL;
}

CTUIX_Node* ctuix_find_node_in_manager_by_id(CTUIX_Manager *ctuix_manager, char *ctuix_node_id)
{
    return ctuix_find_node_by_id(ctuix_manager->ctuix_scene->root_node, ctuix_node_id);
}

void ctuix_tree_draw(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if(ctuix_node->draw)
    {
        ctuix_node->draw(ctuix_node);
    }

    CTUIX_Node *ctuix_node_child = ctuix_node->children;
    while(ctuix_node_child)
    {
        ctuix_tree_draw(ctuix_node_child);
        ctuix_node_child = ctuix_node_child->next;
    }
    if(ctuix_node->window)
    {
        wrefresh(ctuix_node->window);
    }
}

void ctuix_node_free(CTUIX_Node *ctuix_node)
{
    if (!ctuix_node) return;

    if (ctuix_node->window) delwin(ctuix_node->window);
    if (ctuix_node->name) free(ctuix_node->name);
    if (ctuix_node->id) free(ctuix_node->id);
    
    CTUIX_Node *child_node = ctuix_node->children;
    while(child_node)
    {
        CTUIX_Node *next_node = child_node->next;
        ctuix_node_free(child_node);
        child_node = next_node;
    }
    free(ctuix_node);
}