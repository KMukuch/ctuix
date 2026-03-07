#ifndef CTUIX_DRAW_H
#define CTUIX_DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_manager.h"

int ctuix_count_children(CTUIX_Node *ctuix_node);

void ctuix_draw_root(CTUIX_Node *ctuix_node);
void ctuix_draw_panel(CTUIX_Node *ctuix_node);
void ctuix_draw_selection_box(CTUIX_Node *ctuix_node);
void ctuix_draw_label(CTUIX_Node *ctuix_node);
void ctuix_draw_button(CTUIX_Node *ctuix_node);
void ctuix_draw_dispatcher(CTUIX_Node *ctuix_node);

void ctuix_update_selection(CTUIX_Node *ctuix_current_node, CTUIX_Node *ctuix_next_node);

void ctuix_draw_tree(CTUIX_Node *ctuix_node);

#endif