#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_selection_box.h"
#include "ctuix_root.h"
#include "ctuix_nav.h"

CTUIX_Selection_Box* ctuix_selection_box_create()
{
    CTUIX_Selection_Box *ctuix_selection_box = calloc(1, sizeof(CTUIX_Selection_Box));
    if(!ctuix_selection_box)
    {
        return NULL;
    }

    // set up the base node
    ctuix_selection_box->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_selection_box->base_node.draw = ctuix_selection_box_draw;
    ctuix_selection_box->base_node.key_handler = ctuix_selection_box_key_handler;

    return ctuix_selection_box;
}

CTUIX_Item* ctuix_item_create()
{
    CTUIX_Item *ctuix_item = calloc(1, sizeof(CTUIX_Item));
    if(!ctuix_item)
    {
        return NULL;
    }

    // set up the base node
    ctuix_item->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_item->base_node.draw = ctuix_item_draw;
    ctuix_item->base_node.key_handler = ctuix_item_key_handler;


    return ctuix_item;
}

CTUIX_Node* ctuix_selection_box_key_handler(CTUIX_Node *ctuix_node)
{
    int ch = wgetch(ctuix_node->window);
    if(ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        if(next_node)
        {
            current_active->active = false;
            next_node->active = true;
            ctuix_tree_draw(current_active);
            ctuix_tree_draw(next_node);

            return next_node;
        }
    }
    else if(ch == KEY_DOWN)
    {
        
    }
    else if(ch == 'q')
    {
        return NULL;
    }

    return ctuix_node;
}

CTUIX_Node* ctuix_item_key_handler(CTUIX_Node *ctuix_node)
{
    // int ch = wgetch(ctuix_node->parent->window);
    // if(*ch == KEY_UP)
    // {
    //     if(ctuix_node->parent->selected_index > 0)
    //     {
    //         ctuix_node->parent->selected_index--;
    //         if(ctuix_node->parent->selected_index < ctuix_node->parent->scroll_offset)
    //         {
    //             ctuix_node->parent->scroll_offset = ctuix_node->parent->selected_index;
    //         }
    //         ctuix_draw_tree(ctuix_node->parent);  
    //     }
    //     return ctuix_find_item_by_ind(ctuix_node->parent);
    // }
    // else if(*ch == KEY_DOWN)
    // {
    //     if(ctuix_node->parent->selected_index < ctuix_count_children(ctuix_node->parent) - 1)
    //     {
    //         ctuix_node->parent->selected_index++;
    //         if(ctuix_node->parent->selected_index >= ctuix_node->parent->scroll_offset + ctuix_node->parent->visible)
    //         {
    //             ctuix_node->parent->scroll_offset = ctuix_node->parent->selected_index - ctuix_node->parent->visible + 1;
    //         }
    //         ctuix_draw_tree(ctuix_node->parent);  
    //     }
    //     return ctuix_find_item_by_ind(ctuix_node->parent);
    // }
    // else if(*ch == '\t')
    // {
    //     CTUIX_Node *current_active = ctuix_node->parent;
    //     CTUIX_Node *next_node = ctuix_select_next_window(current_active);
    //     if(next_node)
    //     {
    //         current_active->active = false;
    //         next_node->active = true;
    //         ctuix_draw_tree(current_active);
    //         ctuix_draw_tree(next_node);

    //         return next_node;
    //     }
    // }
}

void ctuix_selection_box_draw(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;
    
    if(!ctuix_node->window)
    {
        int max_y, max_x;
        getmaxyx(ctuix_node->parent->window, max_y, max_x);
        if(ctuix_node->ctuix_element_x_alignment == CTUIX_ELEMENT_X_ALIGNMENT_CENTER)
        {
            ctuix_node->x = (max_x - ctuix_node->w) / 2;
        }
        if(ctuix_node->ctuix_element_y_alignment == CTUIX_ELEMENT_Y_ALIGNMENT_CENTER)
        {
            ctuix_node->y = (max_y - ctuix_node->h) / 2;
        }

        ctuix_node->window = derwin(ctuix_node->parent->window, ctuix_node->h, ctuix_node->w, ctuix_node->y, ctuix_node->x);
    }
    if(ctuix_node->window)
    {
        keypad(ctuix_node->window, TRUE);
        werase(ctuix_node->window);
        if(ctuix_node->active)
        {
            wattron(ctuix_node->window, A_REVERSE);
            box(ctuix_node->window, 0, 0);
            wattroff(ctuix_node->window, A_REVERSE);
        }
        else
        {
            wattroff(ctuix_node->window, A_REVERSE);
            box(ctuix_node->window, 0, 0);
        }
        if(ctuix_node->name)
        {
            mvwprintw(ctuix_node->window, 0, 1, "%s", ctuix_node->name);
        }
        mvwaddch(ctuix_node->window, 1, ctuix_node->w / 2, '>');
        mvwaddch(ctuix_node->window, ctuix_node->h - 2, ctuix_node->w / 2, '<');
        wrefresh(ctuix_node->window);
    }
}

void ctuix_item_draw(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    CTUIX_Item *ctuix_item = (CTUIX_Item*)ctuix_node;
    CTUIX_Selection_Box *ctuix_selection_box = (CTUIX_Selection_Box*)ctuix_node->parent;
    
    if(ctuix_node->parent->window)
    {
        if (ctuix_item->index >= ctuix_selection_box->scroll_offset && ctuix_item->index < ctuix_selection_box->scroll_offset + ctuix_selection_box->visible)
        {
            int row = 2 + (ctuix_item->index - ctuix_selection_box->scroll_offset);
            if (ctuix_selection_box->selected_index == ctuix_item->index)
            {
                wattron(ctuix_node->parent->window, A_REVERSE);
                mvwprintw(ctuix_node->parent->window, row, ctuix_node->x, "%s", ctuix_item->value);
                wattroff(ctuix_node->parent->window, A_REVERSE);
            }
            else
            {
                mvwprintw(ctuix_node->parent->window, row, ctuix_node->x, "%s", ctuix_item->value);
            }
        }
        wrefresh(ctuix_node->parent->window);
    }
}

CTUIX_Node* ctuix_find_item_by_ind(CTUIX_Node *ctuix_node)
{
    
}

void ctuix_item_set_ind(CTUIX_Item *ctuix_item)
{
    if(ctuix_item) return;

    CTUIX_Node *parent = ctuix_item->base_node.parent;
    if(!parent) return;

    CTUIX_Node *child = parent->children;
    
    int i = 0;
    while(child)
    {
        if (child == &ctuix_item->base_node)
        {
            ctuix_item->index = i;
            return;
        }
        child = child->next;
        i++;
    }
}

void ctuix_selection_box_set_item_count(CTUIX_Selection_Box *ctuix_selection_box)
{

}
