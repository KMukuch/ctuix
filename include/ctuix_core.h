#ifndef CTUIX_CORE_H
#define CTUIX_CORE_H

#include <stdio.h>
#include "ctuix_tree.h"
#include "ctuix_parse.h"

void ctuix_init();

int ctuix_run(CTUIX_Manager *ctuix_manager);

void ctuix_end();

#endif