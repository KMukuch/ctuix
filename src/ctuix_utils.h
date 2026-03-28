#ifndef CTUIX_UTILS_H
#define CTUIX_UTILS_H

#include <stdio.h>
#include "ctuix_tree.h"
#include "ctuix_parse.h"

void ctuix_set_on_click(CTUIX_Manager *ctuix_manager, char *file_path, char *ctuix_node_id, CTUIX_Event (*on_click)(CTUIX_Node*, void *user_data), void *user_data);
char** ctuix_wrap_value(CTUIX_Node *ctuix_node);

#endif