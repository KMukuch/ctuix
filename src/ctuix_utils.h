#ifndef CTUIX_UTILS_H
#define CTUIX_UTILS_H

#include <stdio.h>
#include "ctuix_tree.h"
#include "ctuix_parse.h"

int ctuix_count_children(CTUIX_Node *ctuix_node);

CTUIX_Node* ctuix_select_next_window(CTUIX_Node *ctuix_node);
CTUIX_Node* ctuix_select_next_item(CTUIX_Node *ctuix_node);

void ctuix_update_selection(CTUIX_Node *ctuix_current_node, CTUIX_Node *ctuix_next_node);

CTUIX_Node* ctuix_find_node_by_id(CTUIX_Node *ctuix_node, char *ctuix_node_id);
CTUIX_Manager* ctuix_find_manager_by_path(CTUIX_Manager *ctuix_manager, char *file_path);

void ctuix_set_on_click(CTUIX_Manager *ctuix_manager, char *file_path, char *ctuix_node_id, CTUIX_Event (*on_click)(CTUIX_Node*, void *user_data), void *user_data);

#endif