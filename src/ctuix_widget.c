#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_widget.h"

CTUIX_Widget widget_create(CTUIX_Widget_Type ctuix_widget_type, int x, int y, int w, int h, bool user_input)
{
    CTUIX_Widget ctuix_widget;

    ctuix_widget.ctuix_widget_type = ctuix_widget_type;
    ctuix_widget.x = x;
    ctuix_widget.y = y;
    ctuix_widget.w = w;
    ctuix_widget.h = h;
    ctuix_widget.user_input = user_input;

    ctuix_widget.parent = NULL;
    ctuix_widget.children = NULL;
    ctuix_widget.next = NULL;

    ctuix_widget.draw = NULL;
    ctuix_widget.handle_key = NULL;

    return ctuix_widget;
}

void widget_draw(CTUIX_Widget *ctuix_widget, WINDOW *window)
{

}

void widget_handle_key(CTUIX_Widget *ctuix_widget, int key)
{

}