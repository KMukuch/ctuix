#ifndef CTUIX_DRAW_H
#define CTUIX_DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

void ctuix_node_draw_default(CTUIX_Node *ctuix_node);

void ctuix_tree_draw(CTUIX_Node *ctuix_node);

#endif