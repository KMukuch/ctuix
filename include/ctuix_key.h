#ifndef CTUIX_KEY_H
#define CTUIX_KEY_H

#include <ncurses.h>
#include "ctuix_tree.h"

typedef enum {
    CTUIX_KEY_NONE,
    CTUIX_KEY_QUIT,
    CTUIX_KEY_TAB_NEXT,
    CTUIX_KEY_UP,
    CTUIX_KEY_DOWN,
    CTUIX_KEY_LEFT,
    CTUIX_KEY_RIGHT,
    CTUIX_KEY_ENTER,
    CTUIX_KEY_BACKSPACE
} CTUIX_KeyAction;

int ctuix_key_listener(CTUIX_Node *ctuix_node);

#endif