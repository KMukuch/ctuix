#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/valid.h>
#include "ctuix_parse.h"

static bool _user_interaction_enabled(CTUIX_Element_Type ctuix_element_type)
{
    if(ctuix_element_type == CTUIX_ELEMENT_LABEL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

static CTUIX_Element_Type _get_ctuix_element_type(xmlChar *node_type)
{
    if(xmlStrcmp(node_type, BAD_CAST "ctuix") == 0)
    {
        return CTUIX_ELEMENT_ROOT;
    }
    else if(xmlStrcmp(node_type, BAD_CAST "ctuix_panel") == 0)
    {
        return CTUIX_ELEMENT_PANEL;
    }
    else if(xmlStrcmp(node_type, BAD_CAST "ctuix_selection_box") == 0)
    {
        return CTUIX_ELEMENT_SELECTION_BOX;
    }
    else if(xmlStrcmp(node_type, BAD_CAST "ctuix_scroll_panel") == 0)
    {
        return CTUIX_ELEMENT_SCROLL_PANEL;
    }
    else if(xmlStrcmp(node_type, BAD_CAST "ctuix_label") == 0)
    {
        return CTUIX_ELEMENT_LABEL;
    }
    else if(xmlStrcmp(node_type, BAD_CAST "ctuix_button") == 0)
    {
        return CTUIX_ELEMENT_BUTTON;
    }
    else if(xmlStrcmp(node_type, BAD_CAST "ctuix_entry") == 0)
    {
        return CTUIX_ELEMENT_ENTRY;
    }
    else
    {
        return CTUIX_ELEMENT_ERROR;
    }
}

static CTUIX_Node* _build_ctuix_node(xmlNode *xml_node)
{
    int x = 0, y = 0, w = 0, h = 0;
    char* name_copy = NULL;
    char* content_copy = NULL;

    CTUIX_Node *ctuix_node;
    
    xmlChar *node_x = xmlGetProp(xml_node, BAD_CAST "x");
    xmlChar *node_y = xmlGetProp(xml_node, BAD_CAST "y");
    xmlChar *node_w = xmlGetProp(xml_node, BAD_CAST "w");
    xmlChar *node_h = xmlGetProp(xml_node, BAD_CAST "h");
    xmlChar *node_name = xmlGetProp(xml_node, BAD_CAST "name");
    xmlChar *node_type = xmlStrdup(xml_node->name);
    xmlChar* node_content = xmlNodeGetContent(xml_node);
    
    if(node_x) x = atoi((char *)node_x);
    if(node_y) y = atoi((char *)node_y);
    if(node_w) w = atoi((char *)node_w);
    if(node_h) h = atoi((char *)node_h);
    
    if(node_name) name_copy = strdup((char*)node_name);
    if(node_content) content_copy = strdup((char*)node_content);
    
    ctuix_node = ctuix_node_create(_get_ctuix_element_type(node_type), x, y, w, h, _user_interaction_enabled(_get_ctuix_element_type(node_type)), name_copy, content_copy);
    
    if(node_x) xmlFree(node_x);
    if(node_y) xmlFree(node_y);
    if(node_w) xmlFree(node_w);
    if(node_h) xmlFree(node_h);
    if(node_name) xmlFree(node_name);
    if(node_type) xmlFree(node_type);
    if(node_content) xmlFree(node_content);
    
    return ctuix_node;
}

static void _read_xml_node(xmlNode *xml_node, CTUIX_Node *parent_ctuix_node)
{
    xmlNode *current_node = xml_node->children;
    CTUIX_Node *prev_ctuix_child = NULL;
    while (current_node)
    {
        if (current_node->type == XML_ELEMENT_NODE)
        {
            CTUIX_Node *ctuix_node = _build_ctuix_node(current_node);
            ctuix_node->parent = parent_ctuix_node;
            if(prev_ctuix_child)
            {
                prev_ctuix_child->next = ctuix_node;
            }
            else
            {
                parent_ctuix_node->children = ctuix_node;
            }
            prev_ctuix_child = ctuix_node;
            
            _read_xml_node(current_node, ctuix_node);
        }
        current_node = current_node->next;
    }
}

CTUIX_Node* ctuix_parse(char *file_path)
{
    xmlDoc *xml_doc = xmlReadFile(file_path, NULL, XML_PARSE_DTDLOAD);
    xmlNode *xml_root = xmlDocGetRootElement(xml_doc);
    CTUIX_Node *ctuix_root = _build_ctuix_node(xml_root);
    _read_xml_node(xml_root, ctuix_root);

    xmlFreeDoc(xml_doc);
    xmlCleanupParser();

    return ctuix_root;
}

void ctuix_delete(CTUIX_Node *ctuix_node)
{
    if(ctuix_node)
    {
        ctuix_node_free(ctuix_node);
        ctuix_node = NULL;
    }
}