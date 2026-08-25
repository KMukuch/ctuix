#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

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

    return root;
}
