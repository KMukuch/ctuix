#ifndef CTUIX_CORE_H
#define CTUIX_CORE_H

#include <stdio.h>
#include "ctuix_tree.h"
#include "ctuix_parse.h"

void ctuix_core_init();

int ctuix_core_run(CTUIX_Manager *ctuix_manager);

void ctuix_core_end();

#endif