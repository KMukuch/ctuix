#ifndef WIDGET_H
#define WIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

typedef enum {
    CTUIX_WIDGET_PANEL,
    CTUIX_WIDGET_SELECTION_BOX,
    CTUIX_WIDGET_SCROLL_PANEL,
    CTUIX_WIDGET_LABEL,
    CTUIX_WIDGET_BUTTON,
    CTUIX_WIDGET_ENTRY_BOX
} CTUIX_Widget_Type;

typedef struct CTUIX_Widget {
    CTUIX_Widget_Type ctuix_widget_type;
    int x, y, w, h;
    bool user_input;
    bool active;

    struct CTUIX_Widget *parent;
    struct CTUIX_Widget *children;
    struct CTUIX_Widget *next;

    void (*draw)(struct CTUIX_Widget *ctuix_widget, WINDOW *window);
    void (*handle_key)(struct CTUIX_Widget *ctuix_widget, int key);
} CTUIX_Widget;

CTUIX_Widget widget_create(CTUIX_Widget_Type ctuix_widget_type, int x, int y, int w, int h, bool user_input);
void widget_draw(CTUIX_Widget *ctuix_widget, WINDOW *window);
void widget_handle_key(CTUIX_Widget *ctuix_widget, int key);

#endif
