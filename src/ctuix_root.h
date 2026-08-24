#ifndef CTUIX_DRAW_H
#define CTUIX_DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

void ctuix_draw_root(CTUIX_Node *ctuix_node);

CTUIX_Node* ctuix_key_handler_root(CTUIX_Node *ctuix_node);

#endif