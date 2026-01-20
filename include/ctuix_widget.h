#ifndef CTUIX_WIDGET_H
#define CTUIX_WIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

typedef enum {
    CTUIX_ROOT,
    CTUIX_PANEL,
    CTUIX_SELECTION_BOX,
    CTUIX_SCROLL_PANEL,
    CTUIX_LABEL,
    CTUIX_BUTTON,
    CTUIX_ENTRY
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

CTUIX_Widget ctuix_widget_create(CTUIX_Widget_Type ctuix_widget_type, int x, int y, int w, int h, bool user_input);
void ctuix_widget_draw(CTUIX_Widget *ctuix_widget, WINDOW *window);
void ctuix_widget_handle_key(CTUIX_Widget *ctuix_widget, int key);

#endif
