#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include "ctuix_scroll_panel.h"
#include "ctuix_root.h"
#include "ctuix_nav.h"

CTUIX_Scroll_Panel* ctuix_scroll_panel_create()
{
    CTUIX_Scroll_Panel *ctuix_scroll_panel = calloc(1, sizeof(CTUIX_Scroll_Panel));
    if(!ctuix_scroll_panel)
    {
        return NULL;
    }

    // set up the base node
    ctuix_scroll_panel->base_node.ctuix_element_type = CTUIX_ELEMENT_PANEL;
    ctuix_scroll_panel->base_node.draw = ctuix_scroll_panel_draw;
    ctuix_scroll_panel->base_node.key_handler = ctuix_scroll_panel_key_handler;

    return ctuix_scroll_panel;
}

CTUIX_Node* ctuix_scroll_panel_key_handler(CTUIX_Node *ctuix_node)
{
    int ch = wgetch(ctuix_node->window);
    CTUIX_Scroll_Panel *ctuix_scroll_panel = (CTUIX_Scroll_Panel*)ctuix_node;
    if(ch == KEY_UP)
    {
        if(ctuix_scroll_panel->scroll_offset > 0)
        {
            ctuix_scroll_panel->scroll_offset--;
            ctuix_tree_draw(ctuix_node);
        }
    }
    else if(ch == KEY_DOWN)
    {
        if(ctuix_scroll_panel->scroll_offset < ctuix_scroll_panel->line_count - 1)
        {
            ctuix_scroll_panel->scroll_offset++;
            ctuix_tree_draw(ctuix_node);
        }
    }
    else if(ch == '\t')
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
    else if(ch == 'q')
    {
        return NULL;
    }

    return ctuix_node;
}

void ctuix_scroll_panel_draw(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;

    CTUIX_Scroll_Panel *ctuix_scroll_panel = (CTUIX_Scroll_Panel*)ctuix_node;
    
    if(!ctuix_node->window)
    {
        int max_y, max_x;
        getmaxyx(ctuix_node->parent->window, max_y, max_x);
        if(ctuix_node->ctuix_element_w_units == CTUIX_ELEMENT_UNITS_VW)
        {
            int vw = max_x * ctuix_node->w / 100;
            ctuix_node->w = vw;
        }
        if(ctuix_node->ctuix_element_h_units == CTUIX_ELEMENT_UNITS_VH)
        {
            int vh = max_y * ctuix_node->h / 100;
            ctuix_node->h = vh;
        }
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
        char **wrapped_value = ctuix_scroll_panel_wrap_value(ctuix_node);
        if(wrapped_value)
        {
            for(int i = 0; i + ctuix_scroll_panel->scroll_offset < ctuix_scroll_panel->line_count && i < ctuix_node->h - 2; i++)
            {
                mvwprintw(ctuix_node->window, i + 1, 1, "%s", wrapped_value[i + ctuix_scroll_panel->scroll_offset]);
                free(wrapped_value[i]);
            }
            free(wrapped_value);
        }
        if(ctuix_node->name)
        {
            mvwprintw(ctuix_node->window, 0, 1, "%s", ctuix_node->name);
        }
        wrefresh(ctuix_node->window);
    }
}

void ctuix_scroll_panel_set_value(CTUIX_Node *ctuix_node, char* value)
{
    if(!ctuix_node) return;
    if(ctuix_node->ctuix_element_type != CTUIX_ELEMENT_SCROLL_PANEL) return;
    if(!value) return;

    CTUIX_Scroll_Panel *ctuix_scroll_panel = (CTUIX_Scroll_Panel*)ctuix_node;
    ctuix_scroll_panel->value = strdup(value);
}

char** ctuix_scroll_panel_wrap_value(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return NULL;

    CTUIX_Scroll_Panel *ctuix_scroll_panel = (CTUIX_Scroll_Panel*)ctuix_node;

    if(!ctuix_scroll_panel->value) return NULL;

    int max_lines = strlen(ctuix_scroll_panel->value) + 1;
    int line_count = 0;
    char *text = ctuix_scroll_panel->value;
    char **lines = malloc(max_lines * sizeof(char*));
    if(!lines) return NULL;
    
    if(text)
    {
        int width = ctuix_node->w - 2;
        int start = 0;
        int len = strlen(text);
        
        for (int i = 0; i < max_lines && start < len; i++)
        {
            // Calculate end
            int end = start + width;
            if (end >= len) end = len;
            
            // Look back for a space to break at (if not last line)
            int break_point = end;
            if (end < len)
            {
                while (break_point > start && !isspace(text[break_point]))
                {
                    break_point--;
                }
                if (break_point > start) end = break_point;  // break at space
            }
            
            // Copy the line
            int line_len = end - start;
            lines[i] = malloc(line_len + 1);
            if (!lines[i])
            {
                // cleanup on failure
                for (int j = 0; j < i; j++) 
                {
                    free(lines[j]);
                }
                free(lines);
                return NULL;
            }
            
            strncpy(lines[i], text + start, line_len);
            lines[i][line_len] = '\0';
            
            // Move start to next line (skip space if present)
            start = end;
            if (start < len && isspace(text[start])) start++;

            line_count++;
        }
        ctuix_scroll_panel->line_count = line_count;
    }
    
    char **result = realloc(lines, line_count * sizeof(char*));
    if(result)
    {
        return result;
    }
    else
    {
        return lines;
    }
}