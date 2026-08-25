#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/valid.h>
#include "ctuix_error.h"
#include "ctuix_parse.h"
#include "ctuix_tree.h"
#include "ctuix_button.h"
#include "ctuix_entry.h"
#include "ctuix_label.h"
#include "ctuix_panel.h"
#include "ctuix_scroll_panel.h"
#include "ctuix_selection_box.h"
#include "ctuix_root.h"

static bool _focusable(CTUIX_Element_Type ctuix_element_type)
{
    if(ctuix_element_type == CTUIX_ELEMENT_LABEL || ctuix_element_type == CTUIX_ELEMENT_ITEM)
    {
        return false;
    }
    else
    {
        return true;
    }
}

static bool _input(CTUIX_Element_Type ctuix_element_type)
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
    else if(xmlStrcmp(node_type, BAD_CAST "ctuix_item") == 0)
    {
        return CTUIX_ELEMENT_ITEM;
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

static CTUIX_Element_X_Alignment _get_ctuix_element_x_alignment(xmlChar *x_alignment)
{
    if(xmlStrcmp(x_alignment, BAD_CAST "center") == 0)
    {
        return CTUIX_ELEMENT_X_ALIGNMENT_CENTER;
    }
    else
    {
        return CTUIX_ELEMENT_X_ALIGNMENT_AUTO;
    }
}

static CTUIX_Element_Y_Alignment _get_ctuix_element_y_alignment(xmlChar *y_alignment)
{
    if(xmlStrcmp(y_alignment, BAD_CAST "center") == 0)
    {
        return CTUIX_ELEMENT_Y_ALIGNMENT_CENTER;
    }
    else
    {
        return CTUIX_ELEMENT_Y_ALIGNMENT_AUTO;
    }
}

static CTUIX_Node* _build_ctuix_widget(CTUIX_Element_Type ctuix_element_type)
{
    if(ctuix_element_type == CTUIX_ELEMENT_ROOT)
    {
        CTUIX_Root *ctuix_root = ctuix_root_create();

        return (CTUIX_Node*)ctuix_root; 
    }
    else if(ctuix_element_type == CTUIX_ELEMENT_PANEL)
    {
        CTUIX_Panel *ctuix_panel = ctuix_panel_create();

        return (CTUIX_Node*)ctuix_panel;
    }
    else if(ctuix_element_type == CTUIX_ELEMENT_SELECTION_BOX)
    {
        CTUIX_Selection_Box *ctuix_selection_box = ctuix_selection_box_create();

        return (CTUIX_Node*)ctuix_selection_box;
    }
    else if(ctuix_element_type == CTUIX_ELEMENT_SCROLL_PANEL)
    {
        CTUIX_Scroll_Panel *ctuix_scroll_panel = ctuix_scroll_panel_create();

        return (CTUIX_Node*)ctuix_scroll_panel;
    }
    else if(ctuix_element_type == CTUIX_ELEMENT_ITEM)
    {
        CTUIX_Item *ctuix_item = ctuix_item_create();

        return (CTUIX_Node*)ctuix_item;
    }
    else if(ctuix_element_type == CTUIX_ELEMENT_LABEL)
    {
        CTUIX_Label *ctuix_label = ctuix_label_create();
        
        return (CTUIX_Node*)ctuix_label;
    }
    else if(ctuix_element_type == CTUIX_ELEMENT_BUTTON)
    {
        CTUIX_Button *ctuix_button = ctuix_button_create();

        return (CTUIX_Node*)ctuix_button;
    }
    else if(ctuix_element_type == CTUIX_ELEMENT_ENTRY)
    {
        CTUIX_Entry *ctuix_entry = ctuix_entry_create();

        return (CTUIX_Node*)ctuix_entry;   
    }
    else
    {
        return NULL;
    }
}

static CTUIX_Node* _build_ctuix_node(xmlNode *xml_node)
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    char* name_copy = NULL;
    char* content_copy = NULL;
    char* id_copy = NULL;

    CTUIX_Node *ctuix_node;

    CTUIX_Element_Units ctuix_element_y_units = CTUIX_ELEMENT_UNITS_AUTO;
    CTUIX_Element_Units ctuix_element_x_units = CTUIX_ELEMENT_UNITS_AUTO;
    CTUIX_Element_Units ctuix_element_h_units = CTUIX_ELEMENT_UNITS_AUTO;
    CTUIX_Element_Units ctuix_element_w_units = CTUIX_ELEMENT_UNITS_AUTO;
    
    xmlChar *node_x = xmlGetProp(xml_node, BAD_CAST "x");
    xmlChar *node_y = xmlGetProp(xml_node, BAD_CAST "y");
    xmlChar *node_w = xmlGetProp(xml_node, BAD_CAST "w");
    xmlChar *node_h = xmlGetProp(xml_node, BAD_CAST "h");
    xmlChar *node_name = xmlGetProp(xml_node, BAD_CAST "name");
    xmlChar *node_type = xmlStrdup(xml_node->name);
    xmlChar *node_x_alignment = xmlGetProp(xml_node, BAD_CAST "x-alignment");
    xmlChar *node_y_alignment = xmlGetProp(xml_node, BAD_CAST "y-alignment");
    xmlChar *node_content = xmlNodeGetContent(xml_node);
    xmlChar *node_id = xmlGetProp(xml_node, BAD_CAST "id");
    
    CTUIX_Element_Type ctuix_element_type = _get_ctuix_element_type(node_type);

    if(node_x)
    {
        // if(strstr(node_x, "vw"))
        // {
        //     ctuix_element_x_units = CTUIX_ELEMENT_UNITS_VW;
        // }
        
        x = atoi((char *)node_x);
    }
    if(node_y) 
    {
        // if(strstr(node_y, "vw"))
        // {
        //     ctuix_element_y_units = CTUIX_ELEMENT_UNITS_VW;
        // }
        
        y = atoi((char *)node_y);
    }
    if(node_w) 
    {
        if(strstr((char *)node_w, "vw"))
        {
            ctuix_element_w_units = CTUIX_ELEMENT_UNITS_VW;
        }
        
        w = atoi((char *)node_w);
    }
    if(node_h) 
    {
        if(strstr((char *)node_h, "vh"))
        {
            ctuix_element_h_units = CTUIX_ELEMENT_UNITS_VH;
        }
        
        h = atoi((char *)node_h);
    }
    
    if(node_name) name_copy = strdup((char*)node_name);
    if(node_content) content_copy = strdup((char*)node_content);
    if(node_id) id_copy = strdup((char*)node_id);
    
    ctuix_node = _build_ctuix_widget(ctuix_element_type);
    ctuix_node_set_meta(ctuix_node, ctuix_element_type, name_copy, id_copy);
    ctuix_node_set_layout(ctuix_node, ctuix_element_x_units, ctuix_element_y_units, ctuix_element_w_units, ctuix_element_h_units, _get_ctuix_element_x_alignment(node_x_alignment), _get_ctuix_element_y_alignment(node_y_alignment), x, y, w, h);
    ctuix_node_set_flags(ctuix_node, _focusable(ctuix_element_type), _input(ctuix_element_type));
    
    ctuix_label_set_value(ctuix_node, content_copy);
    ctuix_button_set_value(ctuix_node, content_copy);
    ctuix_scroll_panel_set_value(ctuix_node, content_copy);

    if(node_x) xmlFree(node_x);
    if(node_y) xmlFree(node_y);
    if(node_w) xmlFree(node_w);
    if(node_h) xmlFree(node_h);
    if(node_name) xmlFree(node_name);
    if(node_type) xmlFree(node_type);
    if(node_content) xmlFree(node_content);
    if(node_id) xmlFree(node_id);
    
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

CTUIX_Manager* ctuix_parse(char *file_path)
{
    xmlDoc *xml_doc = xmlReadFile(file_path, NULL, XML_PARSE_DTDLOAD | XML_PARSE_DTDVALID);
    if(!xml_doc)
    {
        ctuix_error_show("Error", "File not parsed!");
        return NULL;
    }

    xmlNode *xml_root = xmlDocGetRootElement(xml_doc);
    CTUIX_Node *ctuix_root = _build_ctuix_node(xml_root);
    CTUIX_Manager *ctuix_manager = ctuix_manager_create(ctuix_root, file_path);
    _read_xml_node(xml_root, ctuix_root);

    xmlFreeDoc(xml_doc);

    return ctuix_manager;
}

CTUIX_Manager* ctuix_parse_multiple(char **file_path_array, int count)
{
    CTUIX_Manager *head = NULL;
    CTUIX_Manager *tail = NULL;

    for (int i = 0; i < count; i++)
    {
        CTUIX_Manager *ctuix_manager = ctuix_parse(file_path_array[i]);

        if (ctuix_manager)
        {
            if(!head)
            {
                head = ctuix_manager;
                tail = ctuix_manager;
            }
            else
            {
                tail->next = ctuix_manager;
                ctuix_manager->previous = tail;
                tail = ctuix_manager;
            }
        }
    }
    return head;
}

void ctuix_delete(CTUIX_Manager *ctuix_manager)
{
    while (ctuix_manager)
    {
        CTUIX_Manager *next = ctuix_manager->next;
        if (ctuix_manager->file_name) free(ctuix_manager->file_name);
        ctuix_node_free(ctuix_manager->ctuix_scene->root_node);
        free(ctuix_manager);
        ctuix_manager = next;
    }
}

void ctuix_cleanup()
{
    xmlCleanupParser();
}