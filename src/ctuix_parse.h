#ifndef CTUIX_PARSE_H
#define CTUIX_PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/valid.h>
#include "ctuix_tree.h"

CTUIX_Manager* ctuix_parse(char *file_path);
CTUIX_Manager* ctuix_parse_multiple(char **file_path, int count);

void ctuix_delete(CTUIX_Manager *ctuix_manager);
void ctuix_cleanup();

#endif