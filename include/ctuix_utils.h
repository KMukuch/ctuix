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

void _read_xml_node(xmlNode *xml_node, CTUIX_Node *parent_ctuix_node);
CTUIX_Node* _build_ctuix_node(xmlNode *xml_node);
CTUIX_Element_Type _get_ctuix_element_type(xmlChar *xml_name);
bool _user_interaction_enabled(CTUIX_Element_Type ctuix_element_type);

void ctuix_delete();

#endif