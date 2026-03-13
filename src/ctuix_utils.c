#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_utils.h"
#include "ctuix_draw.h"

int ctuix_count_children(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return 0;
    
    int count = 0;
    CTUIX_Node *current_node = ctuix_node;
    while(current_node)
    {
        count++;
        current_node = current_node->next;
    }
    
    return count;
}

CTUIX_Node* ctuix_select_next_window(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return NULL;

    CTUIX_Node *root = ctuix_node;
    CTUIX_Node *current = ctuix_node;
    CTUIX_Node *child = ctuix_node->children;
    while(child)
    {
        if(child->focusable)
        {
            return child;
        }
        
        CTUIX_Node *child_children = ctuix_select_next_window(child);
        if(child_children)
        {
            return child_children;
        }
        
        child = child->next;
    }

    if(ctuix_node->next)
    {
        if(ctuix_node->next->focusable)
        {
            return ctuix_node->next;
        }
        
        return ctuix_select_next_window(ctuix_node->next);
    }

    while(current->parent)
    {
        if(current->parent->next)
        {
            CTUIX_Node *next_sibling = current->parent->next;
            
            if(next_sibling->focusable)
            {
                return next_sibling;
            }
            
            return ctuix_select_next_window(next_sibling);
        }
        current = current->parent;
    }
    
    while(root->parent)
    {
        root = root->parent;
    }

    return ctuix_select_next_window(root);
}

CTUIX_Node* ctuix_select_next_item(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return NULL;

    if(ctuix_node->children)
    {
        return ctuix_node->children;
    }
    else if(ctuix_node->next)
    {
        return ctuix_node->next;
    }
    else
    {
        return ctuix_node->parent->children;
    }
}

void ctuix_update_selection(CTUIX_Node *ctuix_current_node, CTUIX_Node *ctuix_next_node)
{
    if(!ctuix_current_node) return;

    wattroff(ctuix_current_node->window, A_REVERSE);
    box(ctuix_current_node->window, 0, 0);
    wrefresh(ctuix_current_node->window);

    wattron(ctuix_next_node->window, A_REVERSE);
    box(ctuix_next_node->window, 0, 0);
    wrefresh(ctuix_next_node->window);
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

void ctuix_set_on_click(CTUIX_Manager *ctuix_manager, char *ctuix_node_id, CTUIX_Event (*on_click)(CTUIX_Node* ctuix_node, void *user_data), void *user_data)
{
    if (!ctuix_manager || !ctuix_node_id || !on_click) return;

    CTUIX_Node *ctuix_node = ctuix_find_node_by_id(ctuix_manager->root_node, ctuix_node_id);
    
    if(ctuix_node)
    {
        ctuix_node->on_click = on_click;
    }
}