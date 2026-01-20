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
#include "ctuix_widget.h"

CTUIX_Widget* ctuix_parse(char *file_path);

void ctuix_walk(xmlNode *xml_root);

void ctuix_delete();

#endif