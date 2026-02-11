#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_manager.h"

CTUIX_Manager* ctuix_manager_create(CTUIX_Node *root_node)
{
    CTUIX_Manager *ctuix_manager = malloc(sizeof(CTUIX_Manager));

    ctuix_manager->root_node = root_node;
    ctuix_manager->active_node = root_node;

    ctuix_manager->ch = 0;

    return ctuix_manager;
}