#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_utils.h"
#include "ctuix_manager.h"
#include "ctuix_draw.h"

void ctuix_init()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
}

CTUIX_Node* ctuix_select_next(CTUIX_Node *ctuix_node)
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
        
        CTUIX_Node *child_children = ctuix_select_next(child);
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
        
        return ctuix_select_next(ctuix_node->next);
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
            
            return ctuix_select_next(next_sibling);
        }
        current = current->parent;
    }
    
    while(root->parent)
    {
        root = root->parent;
    }

    return ctuix_select_next(root);
}

CTUIX_Node* ctuix_select_item(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return NULL;

    CTUIX_Node *current_node = ctuix_node->children;
    if(current_node)
    {
        return current_node;
    }
    
    if(current_node->next)
    {
        return current_node->next;
    }
}

int ctuix_key_listener(CTUIX_Node *ctuix_node)
{
    return wgetch(ctuix_node->window);
}

int ctuix_run(CTUIX_Manager *ctuix_manager)
{
    if(!ctuix_manager->root_node) return 0;
    
    ctuix_draw_tree(ctuix_manager->root_node);
    refresh();
    
    ctuix_manager->ch = ctuix_key_listener(ctuix_manager->active_node);

    while(ctuix_manager->ch != 'q')
    {
        CTUIX_Node *current_active = ctuix_manager->active_node;
        if(ctuix_manager->active_node->ctuix_element_type == CTUIX_ELEMENT_SELECTION_BOX)
        {
            ctuix_manager->active_node = ctuix_select_item(ctuix_manager->active_node);
        }
        else
        {
            ctuix_manager->active_node = ctuix_select_next(ctuix_manager->active_node);
        }
        ctuix_update_selection(current_active, ctuix_manager->active_node);
        
        refresh();

        ctuix_manager->ch = ctuix_key_listener(ctuix_manager->active_node);
    }

    return 1;
}

void ctuix_end()
{
    endwin();
}