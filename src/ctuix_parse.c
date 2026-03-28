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
#include "ctuix_draw.h"
#include "ctuix_key.h"
#include "ctuix_utils.h"

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

static void _set_fnc_pointer(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;
    
    if(ctuix_node->ctuix_element_type == CTUIX_ELEMENT_ROOT)
    {
        ctuix_node->draw = ctuix_draw_root;
        ctuix_node->key_handler = ctuix_key_handler_root;
    }
    else if(ctuix_node->ctuix_element_type == CTUIX_ELEMENT_PANEL)
    {
        ctuix_node->draw = ctuix_draw_panel;
        ctuix_node->key_handler = ctuix_key_handler_panel;
    }
    else if(ctuix_node->ctuix_element_type == CTUIX_ELEMENT_SELECTION_BOX)
    {
        ctuix_node->draw = ctuix_draw_selection_box;
        ctuix_node->key_handler = ctuix_key_handler_selection_box;
    }
    else if(ctuix_node->ctuix_element_type == CTUIX_ELEMENT_SCROLL_PANEL)
    {
        ctuix_node->draw = ctuix_draw_scroll_panel;
        ctuix_node->key_handler = NULL;
    }
    else if(ctuix_node->ctuix_element_type == CTUIX_ELEMENT_ITEM)
    {
        ctuix_node->draw = ctuix_draw_item;
        ctuix_node->key_handler = ctuix_key_handler_item;
    }
    else if(ctuix_node->ctuix_element_type == CTUIX_ELEMENT_LABEL)
    {
        ctuix_node->draw = ctuix_draw_label;
        ctuix_node->key_handler = NULL;
    }
    else if(ctuix_node->ctuix_element_type == CTUIX_ELEMENT_BUTTON)
    {
        ctuix_node->draw = ctuix_draw_button;
        ctuix_node->key_handler = ctuix_key_handler_button;
    }
    else if(ctuix_node->ctuix_element_type == CTUIX_ELEMENT_ENTRY)
    {
        ctuix_node->draw = NULL;
        ctuix_node->key_handler = NULL;
    }
    else
    {
        ctuix_node->draw = NULL;
        ctuix_node->key_handler = NULL;
    }
}

static CTUIX_Node* _build_ctuix_node(xmlNode *xml_node)
{
    int x = 0, y = 0, w = 0, h = 0;
    char* name_copy = NULL;
    char* content_copy = NULL;
    char* id_copy = NULL;

    CTUIX_Node *ctuix_node;
    
    xmlChar *node_x = xmlGetProp(xml_node, BAD_CAST "x");
    xmlChar *node_y = xmlGetProp(xml_node, BAD_CAST "y");
    xmlChar *node_w = xmlGetProp(xml_node, BAD_CAST "w");
    xmlChar *node_h = xmlGetProp(xml_node, BAD_CAST "h");
    xmlChar *node_name = xmlGetProp(xml_node, BAD_CAST "name");
    xmlChar *node_type = xmlStrdup(xml_node->name);
    xmlChar* node_content = xmlNodeGetContent(xml_node);
    xmlChar* node_id = xmlGetProp(xml_node, BAD_CAST "id");
    
    if(node_x) x = atoi((char *)node_x);
    if(node_y) y = atoi((char *)node_y);
    if(node_w) w = atoi((char *)node_w);
    if(node_h) h = atoi((char *)node_h);
    
    if(node_name) name_copy = strdup((char*)node_name);
    if(node_content) content_copy = strdup((char*)node_content);
    if(node_id) id_copy = strdup((char*)node_id);

    ctuix_node = ctuix_node_create(_get_ctuix_element_type(node_type), x, y, w, h, _focusable(_get_ctuix_element_type(node_type)),_user_interaction_enabled(_get_ctuix_element_type(node_type)), name_copy, content_copy, id_copy);
    _set_fnc_pointer(ctuix_node);

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

static void _set_default(CTUIX_Node *ctuix_node)
{
    if(!ctuix_node) return;
    
    CTUIX_Node *current_node = ctuix_node->children;
    while(current_node)
    {
        if(current_node->ctuix_element_type == CTUIX_ELEMENT_SELECTION_BOX)
        {
            CTUIX_Node *child = current_node->children;
            current_node->selected_index = 0;
            current_node->scroll_offset = 0;
            current_node->visible = current_node->h - 4;
            for(int i = 0; i < ctuix_count_children(current_node); i++)
            {
                child->selected_index = i;
                child->y = 2 + (i % current_node->visible);
                child->x = 1;
                child->h = 1;
                child->w = child->parent->w - 2;
                child = child->next;
            }
        }
        current_node = current_node->next;
    }
    _set_default(ctuix_node->next);
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
    xmlDoc *xml_doc = xmlReadFile(file_path, NULL, XML_PARSE_DTDLOAD);
    if(!xml_doc)
    {
        return NULL;
    }

    xmlNode *xml_root = xmlDocGetRootElement(xml_doc);
    CTUIX_Node *ctuix_root = _build_ctuix_node(xml_root);
    CTUIX_Manager *ctuix_manager = ctuix_manager_create(ctuix_root, file_path);
    _read_xml_node(xml_root, ctuix_root);
    _set_default(ctuix_root);

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
            if (!head)
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
        else
        {
            ctuix_error_show("Error", "File not parsed!");
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
        ctuix_node_free(ctuix_manager->root_node);
        free(ctuix_manager);
        ctuix_manager = next;
    }
}

void ctuix_cleanup()
{
    xmlCleanupParser();
}