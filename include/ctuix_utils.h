#ifndef CTUIX_UTILS_H
#define CTUIX_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"
#include "ctuix_parse.h"

void ctuix_init();

int ctuix_run(CTUIX_Node *ctuix_node);

void ctuix_end();

#endif