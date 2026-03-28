#ifndef CTUIX_KEY_H
#define CTUIX_KEY_H

#include <ncurses.h>
#include "ctuix_tree.h"

CTUIX_Node* ctuix_key_handler_root(CTUIX_Node *ctuix_node, int *ch);
CTUIX_Node* ctuix_key_handler_panel(CTUIX_Node *ctuix_node, int *ch);
CTUIX_Node* ctuix_key_handler_selection_box(CTUIX_Node *ctuix_node, int *ch);
CTUIX_Node* ctuix_key_handler_scroll_panel(CTUIX_Node *ctuix_node, int *ch);
CTUIX_Node* ctuix_key_handler_item(CTUIX_Node *ctuix_node, int *ch);
CTUIX_Node* ctuix_key_handler_button(CTUIX_Node *ctuix_node, int *ch);

#endif