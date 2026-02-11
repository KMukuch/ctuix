#ifndef CTUIX_MANAGER_H
#define CTUIX_MANAGER_H

#include <stdio.h>
#include "ctuix_tree.h"

typedef struct CTUIX_Manager
{
    CTUIX_Node* root_node;
    CTUIX_Node* active_node;
    
    int ch;
} CTUIX_Manager;

CTUIX_Manager* ctuix_manager_create(CTUIX_Node *root_node);

#endif