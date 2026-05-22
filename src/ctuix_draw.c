#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_draw.h"
#include "ctuix_nav.h"
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
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_selection_box(CTUIX_Node *ctuix_node)
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

void ctuix_draw_item(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;
    
    if(ctuix_node->parent->window)
    {
        if (ctuix_node->selected_index >= ctuix_node->parent->scroll_offset && ctuix_node->selected_index < ctuix_node->parent->scroll_offset + ctuix_node->parent->visible)
        {
            int row = 2 + (ctuix_node->selected_index - ctuix_node->parent->scroll_offset);
            if (ctuix_node->parent->selected_index == ctuix_node->selected_index)
            {
                wattron(ctuix_node->parent->window, A_REVERSE);
                mvwprintw(ctuix_node->parent->window, row, ctuix_node->x, "%s", ctuix_node->value);
                wattroff(ctuix_node->parent->window, A_REVERSE);
            }
            else
            {
                mvwprintw(ctuix_node->parent->window, row, ctuix_node->x, "%s", ctuix_node->value);
            }
        }
        wrefresh(ctuix_node->parent->window);
    }
}

void ctuix_draw_scroll_panel(CTUIX_Node *ctuix_node)
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
        char **wrapped_value = ctuix_wrap_value(ctuix_node);
        if(wrapped_value)
        {
            for(int i = 0; i + ctuix_node->scroll_offset < ctuix_node->line_count && i < ctuix_node->h - 2; i++)
            {
                mvwprintw(ctuix_node->window, i + 1, 1, "%s", wrapped_value[i + ctuix_node->scroll_offset]);
                free(wrapped_value[i]);
            }
            free(wrapped_value);
        }
        if(ctuix_node->name)
        {
            mvwprintw(ctuix_node->window, 0, 0, "%s", ctuix_node->name);
        }
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_label(CTUIX_Node *ctuix_node)
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
        if(ctuix_node->value)
        {
            mvwprintw(ctuix_node->window, 1, 1, "%s", ctuix_node->value);
            wrefresh(ctuix_node->window);
        }
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
        wrefresh(ctuix_node->window);
    }
}

void ctuix_draw_entry(CTUIX_Node *ctuix_node)
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
        mvwprintw(ctuix_node->window, 1, 1, "%s", ctuix_node->buffer);
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
    if(ctuix_node->window)
    {
        wrefresh(ctuix_node->window);
    }
}