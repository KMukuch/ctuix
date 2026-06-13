#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_entry.h"
#include "ctuix_draw.h"
#include "ctuix_nav.h"
#include "ctuix_event.h"

CTUIX_Entry* ctuix_entry_create()
{
    CTUIX_Entry *ctuix_entry = calloc(1, sizeof(CTUIX_Entry));
    if(!ctuix_entry)
    {
        return NULL;
    }

    // set up the base node
    ctuix_entry->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_entry->base_node.draw = NULL;
    ctuix_entry->base_node.key_handler = NULL;

    return ctuix_entry;
}

void ctuix_key_handler_entry(CTUIX_Node *ctuix_node)
{
    int ch = wgetch(ctuix_node->window);

    CTUIX_Entry *ctuix_entry = (CTUIX_Entry*)ctuix_node;
    if(ch == '\t')
    {
        CTUIX_Node *current_active = ctuix_node;
        CTUIX_Node *next_node = ctuix_select_next_window(ctuix_node);
        current_active->active = false;
        next_node->active = true;
        ctuix_draw_tree(current_active);
        ctuix_draw_tree(next_node);

        ctuix_node = next_node;
    }
    else if(ch == '\n' || ch == '\r' || ch == KEY_ENTER)
    {
        ch = wgetch(ctuix_node->window);
        while(ch != '\n' && ch != '\r' && ch != KEY_ENTER)
        {
            ch = wgetch(ctuix_node->window);
            if(ch == '\b' || ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127)
            {
                size_t len = strlen(ctuix_entry->buffer);
                if(len > 0)
                {
                    ctuix_entry->buffer[len - 1] = '\0';
                    ctuix_draw_tree(ctuix_node);
                }
            }
            else
            {
                size_t len = strlen(ctuix_entry->buffer);
                if(len < ctuix_entry->visible)
                {
                    snprintf(ctuix_entry->buffer + len, sizeof(ctuix_entry->buffer) - len, "%c", ch);
                    ctuix_draw_tree(ctuix_node);
                }
            }
        }
    }
}

void ctuix_draw_entry(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    CTUIX_Entry *ctuix_entry = (CTUIX_Entry*)ctuix_node;

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
        mvwprintw(ctuix_node->window, 1, 1, "%s", ctuix_entry->buffer);
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