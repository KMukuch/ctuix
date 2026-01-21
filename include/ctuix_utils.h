#ifndef CTUIX_UTILS_H
#define CTUIX_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/valid.h>
#include "ctuix_tree.h"

CTUIX_Node* ctuix_parse(char *file_path);

void _traverse_node(xmlNode *xml_node);

void ctuix_delete();

#endif