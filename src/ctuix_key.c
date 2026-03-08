#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_key.h"
#include "ctuix_tree.h"
#include "ctuix_utils.h"
#include "ctuix_manager.h"
#include "ctuix_draw.h"

int ctuix_key_listener(CTUIX_Node *ctuix_node)
{
    return wgetch(ctuix_node->window);
}
