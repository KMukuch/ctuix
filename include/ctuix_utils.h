#ifndef CTUIX_UTILS_H
#define CTUIX_UTILS_H

#include <stdio.h>
#include "ctuix_tree.h"
#include "ctuix_parse.h"

void ctuix_init();

CTUIX_Node* ctuix_select_next(CTUIX_Node *ctuix_node);
int ctuix_key_listener(CTUIX_Node *ctuix_node);
int ctuix_run(CTUIX_Manager *ctuix_manager);

void ctuix_end();

#endif