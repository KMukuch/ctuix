#ifndef CTUIX_KEY_H
#define CTUIX_KEY_H

#include <ncurses.h>
#include "ctuix_tree.h"

void ctuix_key_handler_root(CTUIX_Manager *ctuix_manager);
void ctuix_key_handler_panel(CTUIX_Manager *ctuix_manager);
void ctuix_key_handler_selection_box(CTUIX_Manager *ctuix_manager);
void ctuix_key_handler_button(CTUIX_Manager *ctuix_manager);

#endif