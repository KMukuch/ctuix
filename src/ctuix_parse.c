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

static CTUIX_Element_Type _get_ctuix_element_type(xmlChar *xml_name)
{
    if(xmlStrcmp(xml_name, BAD_CAST "ctuix") == 0)
    {
        return CTUIX_ELEMENT_ROOT;
    }
    else if(xmlStrcmp(xml_name, BAD_CAST "ctuix_panel") == 0)
    {
        return CTUIX_ELEMENT_PANEL;
    }
    else if(xmlStrcmp(xml_name, BAD_CAST "ctuix_selection_box") == 0)
    {
        return CTUIX_ELEMENT_SELECTION_BOX;
    }
    else if(xmlStrcmp(xml_name, BAD_CAST "ctuix_scroll_panel") == 0)
    {
        return CTUIX_ELEMENT_SCROLL_PANEL;
    }
    else if(xmlStrcmp(xml_name, BAD_CAST "ctuix_label") == 0)
    {
        return CTUIX_ELEMENT_LABEL;
    }
    else if(xmlStrcmp(xml_name, BAD_CAST "ctuix_button") == 0)
    {
        return CTUIX_ELEMENT_BUTTON;
    }
    else if(xmlStrcmp(xml_name, BAD_CAST "ctuix_entry") == 0)
    {
        return CTUIX_ELEMENT_ENTRY;
    }
    else
    {
        return CTUIX_ELEMENT_ERROR;
    }
}

static char* _get_ctuix_element_name(xmlChar *xml_name)
{

}

static CTUIX_Node* _build_ctuix_node(xmlNode *xml_node)
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    xmlChar *x_value = xmlGetProp(xml_node, BAD_CAST "x");
    xmlChar *y_value = xmlGetProp(xml_node, BAD_CAST "y");
    xmlChar *w_value = xmlGetProp(xml_node, BAD_CAST "w");
    xmlChar *h_value = xmlGetProp(xml_node, BAD_CAST "h");
    xmlChar *name_value = xmlGetProp(xml_node, BAD_CAST "name");
    xmlChar *xml_name = xmlStrdup(xml_node->name);;
    
    if (x_value) x = atoi((char *)x_value);
    if (y_value) y = atoi((char *)y_value);
    if (w_value) w = atoi((char *)w_value);
    if (h_value) h = atoi((char *)h_value);
    CTUIX_Element_Type ctuix_element_type = _get_ctuix_element_type(xml_name);
    bool user_input_enabled = _user_interaction_enabled(ctuix_element_type);
    
    if(x_value) xmlFree(x_value);
    if(y_value) xmlFree(y_value);
    if(w_value) xmlFree(w_value);
    if(h_value) xmlFree(h_value);
    xmlFree(xml_name);

    return ctuix_node_create(ctuix_element_type, x, y, w, h, user_input_enabled, "");
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