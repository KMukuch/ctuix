#ifndef CTUIX_UTILS_H
#define CTUIX_UTILS_H

#include <stdio.h>
#include "ctuix_tree.h"
#include "ctuix_parse.h"

int ctuix_count_children(CTUIX_Node *ctuix_node);

CTUIX_Node* ctuix_select_next_window(CTUIX_Node *ctuix_node);
CTUIX_Node* ctuix_select_next_item(CTUIX_Node *ctuix_node);

void ctuix_update_selection(CTUIX_Node *ctuix_current_node, CTUIX_Node *ctuix_next_node);

#endif