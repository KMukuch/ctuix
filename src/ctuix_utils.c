#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_utils.h"

void ctuix_set_on_click(CTUIX_Manager *ctuix_manager, char *file_path, char *ctuix_node_id, CTUIX_Event (*on_click)(CTUIX_Node* ctuix_node, void *user_data), void *user_data)
{
    if (!ctuix_manager || !ctuix_node_id || !on_click) return;

    CTUIX_Manager *target = ctuix_find_manager_by_path(ctuix_manager, file_path);
    if (!target)
    {
        return;
    }

    CTUIX_Node *node = ctuix_find_node_by_id(target->root_node, ctuix_node_id);
    if (node)
    {
        node->on_click = on_click;
    }
}