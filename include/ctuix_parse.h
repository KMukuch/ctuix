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

CTUIX_Node* ctuix_parse(char *file_path);

void ctuix_delete(CTUIX_Node *ctuix_node);

#endif