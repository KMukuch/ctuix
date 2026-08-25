#ifndef CTUIX_ROOT_H
#define CTUIX_ROOT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

typedef struct CTUIX_Root
{
    CTUIX_Node base_node;

} CTUIX_Root;

CTUIX_Root* ctuix_root_create();

void ctuix_root_draw(CTUIX_Node *ctuix_node);

CTUIX_Node* ctuix_root_key_handler(CTUIX_Node *ctuix_node);

#endif