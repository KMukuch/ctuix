#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/valid.h>
#include "ctuix_utils.h"

CTUIX_Node* ctuix_parse(char *file_path)
{
    xmlDoc *xml_doc = xmlReadFile(file_path, NULL, XML_PARSE_DTDLOAD);

    if (xml_doc)
    {
        xmlNode *xml_root = xmlDocGetRootElement(xml_doc);
        _traverse_node(xml_root);
    }

    xmlFreeDoc(xml_doc);
    xmlCleanupParser();

    return NULL;
}

void _traverse_node(xmlNode *xml_node)
{
    xmlNode *temp_node = xml_node->children;
    while(temp_node)
    {
        if(temp_node->type == XML_ELEMENT_NODE)
        {
            printf("Node: %s\n", temp_node->name);
            if(temp_node->children)
            {
                _traverse_node(temp_node->children);
            }
        }
        temp_node = temp_node->next;
    }
}