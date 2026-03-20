#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_draw.h"
#include "ctuix_utils.h"

void ctuix_draw_root(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if(!ctuix_node->window)
    {
        if(ctuix_node->parent == NULL)
        {
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);
            
            if(ctuix_node->w == 0 || ctuix_node->h == 0)
            {
                ctuix_node->w = max_x;
                ctuix_node->h = max_y;
            }
            
            ctuix_node->window = newwin(ctuix_node->h, ctuix_node->w, 0, 0);
        }
    }
    
    if(ctuix_node->window)
    {
        keypad(ctuix_node->window, TRUE);
        werase(ctuix_node->window);
        box(ctuix_node->window, 0, 0);
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_panel(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if(!ctuix_node->window)
    {
        ctuix_node->window = derwin(ctuix_node->parent->window, ctuix_node->h, ctuix_node->w, ctuix_node->y, ctuix_node->x);
    }
    
    if(ctuix_node->window)
    {
        keypad(ctuix_node->window, TRUE);
        werase(ctuix_node->window);
        box(ctuix_node->window, 0, 0);
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_selection_box(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;
    
    if(!ctuix_node->window)
    {
        ctuix_node->window = derwin(ctuix_node->parent->window, ctuix_node->h, ctuix_node->w, ctuix_node->y, ctuix_node->x);
    }
    if(ctuix_node->window)
    {
        keypad(ctuix_node->window, TRUE);
        werase(ctuix_node->window);
        box(ctuix_node->window, 0, 0);
        mvwaddch(ctuix_node->window, 1, ctuix_node->w / 2, '>');
        ctuix_draw_item_list(ctuix_node->children);
        mvwaddch(ctuix_node->window, ctuix_node->h - 2, ctuix_node->w / 2, '<');
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_item(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if(!ctuix_node->window)
    {
        if(ctuix_node->w && ctuix_node->h)
        {
            ctuix_node->window = derwin(ctuix_node->parent->window, ctuix_node->h, ctuix_node->w, ctuix_node->y, ctuix_node->x);
        }
        else if(ctuix_node->w)
        {
            ctuix_node->window = derwin(ctuix_node->parent->window, 3, ctuix_node->w, ctuix_node->y, ctuix_node->x);
        }
        else if(ctuix_node->h)
        {
            ctuix_node->window = derwin(ctuix_node->parent->window, ctuix_node->h, ctuix_node->parent->w - 2, ctuix_node->y, ctuix_node->x);
        }
        else
        {
            ctuix_node->window = derwin(ctuix_node->parent->window, 3, ctuix_node->parent->w - 2, ctuix_node->y, ctuix_node->x);
        }
    }

    if(ctuix_node->window)
    {
        keypad(ctuix_node->window, TRUE);
        werase(ctuix_node->window);
        box(ctuix_node->window, 0, 0);
        mvwprintw(ctuix_node->window, 1, 1, "%s", ctuix_node->value);
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_item_list(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    CTUIX_Node *current_node = ctuix_node;
    CTUIX_Node *prev_node = NULL;
    for(int i = 0; i < ctuix_count_children(ctuix_node); i++)
    {
        if(!prev_node)
        {
            current_node->y = i + 2;
        }
        else
        {
            current_node->y = i + 2 + prev_node->y;
        }
        current_node->x = 1;
        ctuix_draw_item(current_node);
        prev_node = current_node;
        current_node = current_node->next;
    }
}

void ctuix_draw_label(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if(!ctuix_node->window)
    {
        ctuix_node->window = derwin(ctuix_node->parent->window, 1, strlen(ctuix_node->value), ctuix_node->y, ctuix_node->x);
    }
    
    if(ctuix_node->parent->window)
    {
        mvwprintw(ctuix_node->window, 0, 0, "%s", ctuix_node->value);
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_button(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    if(!ctuix_node->window)
    {
        ctuix_node->window = derwin(ctuix_node->parent->window, ctuix_node->h, ctuix_node->w, ctuix_node->y, ctuix_node->x);
    }
    
    if(ctuix_node->window)
    {
        keypad(ctuix_node->window, TRUE);
        werase(ctuix_node->window);
        if(ctuix_node->value)
        {
            mvwprintw(ctuix_node->window, 1, 1, "%s", ctuix_node->value);
            wrefresh(ctuix_node->window);
        }
        box(ctuix_node->window, 0, 0);
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_tree(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;
    
    if(ctuix_node->draw)
    {
        ctuix_node->draw(ctuix_node);
    }

    CTUIX_Node *ctuix_node_child = ctuix_node->children;
    while(ctuix_node_child)
    {
        ctuix_draw_tree(ctuix_node_child);
        ctuix_node_child = ctuix_node_child->next;
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