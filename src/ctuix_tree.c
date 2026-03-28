#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_draw.h"

CTUIX_Node* ctuix_node_create(CTUIX_Element_Type ctuix_element_type, int x, int y, int w, int h, bool focusable, bool input_enabled, char* name, char* value, char* id)
{
    CTUIX_Node *ctuix_node = malloc(sizeof(CTUIX_Node));
    if(!ctuix_node)
    {
        return NULL;
    }
    ctuix_node->window = NULL;
    
    ctuix_node->ctuix_element_type = ctuix_element_type;
    ctuix_node->x = x;
    ctuix_node->y = y;
    ctuix_node->w = w;
    ctuix_node->h = h;
    ctuix_node->selected_index = 0;
    ctuix_node->scroll_offset = 0;
    ctuix_node->line_count = 0;
    ctuix_node->visible = 0;
    ctuix_node->focusable = focusable;
    ctuix_node->input_enabled = input_enabled;
    ctuix_node->active = false;
    if(name)
    {
        ctuix_node->name = strdup(name);
    }
    else
    {
        ctuix_node->name = NULL;
    }
    
    if(value)
    {
        ctuix_node->value = strdup(value);
    }
    else
    {
        ctuix_node->value = NULL;
    }

    if(id)
    {
        ctuix_node->id = strdup(id);
    }
    else
    {
        ctuix_node->id = NULL;
    }

    ctuix_node->draw = NULL;
    ctuix_node->key_handler = NULL;

    ctuix_node->parent = NULL;
    ctuix_node->children = NULL;
    ctuix_node->next = NULL;

    return ctuix_node;
}

CTUIX_Manager* ctuix_manager_create(CTUIX_Node *root_node, char *file_path)
{
    CTUIX_Manager *ctuix_manager = malloc(sizeof(CTUIX_Manager));

    ctuix_manager->file_name = strdup(file_path);;

    ctuix_manager->root_node = root_node;
    ctuix_manager->active_node = root_node;

    ctuix_manager->current_event = NULL;
    ctuix_manager->event_count = 0;
    ctuix_manager->event_handler = NULL;

    ctuix_manager->ch = 0;

    ctuix_manager->previous = NULL;
    ctuix_manager->next = NULL;

    return ctuix_manager;
}

int ctuix_count_children(CTUIX_Node *ctuix_node)
{
    if (!ctuix_node) return 0;
    int count = 0;
    CTUIX_Node *child = ctuix_node->children;
    while (child) {
        count++;
        child = child->next;
    }
    return count;
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

CTUIX_Node* ctuix_find_item_by_ind(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return 0;
    
    CTUIX_Node *current_node = ctuix_node->children;
    while(current_node)
    {
        if(current_node->selected_index == ctuix_node->selected_index)
        {
            return current_node;
        }
        current_node = current_node->next;
    }
    
    return NULL;
}

void ctuix_node_free(CTUIX_Node *ctuix_node)
{
    if (!ctuix_node) return;

    if (ctuix_node->window) delwin(ctuix_node->window);
    if (ctuix_node->name) free(ctuix_node->name);
    if (ctuix_node->value) free(ctuix_node->value);
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