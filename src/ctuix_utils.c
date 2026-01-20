#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/valid.h>
#include "ctuix_utils.h"

CTUIX_Widget* ctuix_parse(char *file_path)
{
    xmlDoc *xml_doc = xmlReadFile(file_path, NULL, XML_PARSE_DTDLOAD);

    if (xml_doc)
    {
        xmlNode *xml_root = xmlDocGetRootElement(xml_doc);
    }

    xmlFreeDoc(xml_doc);
    xmlCleanupParser();
}