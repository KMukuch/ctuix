#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_button.h"
#include "ctuix_entry.h"
#include "ctuix_label.h"
#include "ctuix_panel.h"
#include "ctuix_scroll_panel.h"
#include "ctuix_selection_box.h"
#include "ctuix_utils.h"

char** ctuix_wrap_value(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return NULL;

    CTUIX_Scroll_Panel *ctuix_scroll_panel = (CTUIX_Scroll_Panel*)ctuix_node;

    if (!ctuix_scroll_panel->value) return NULL;

    int max_lines = strlen(ctuix_scroll_panel->value) + 1;
    int line_count = 0;
    char *text = ctuix_scroll_panel->value;
    char **lines = malloc(max_lines * sizeof(char*));
    if (!lines) return NULL;
    
    if (text)
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