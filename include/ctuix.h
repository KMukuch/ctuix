#ifndef CTUIX_H
#define CTUIX_H

#define CTUIX_VERSION_MAJOR 0
#define CTUIX_VERSION_MINOR 0
#define CTUIX_VERSION_PATCH 0

typedef enum CTUIX_Element_Type;

typedef struct CTUIX_Node;
typedef struct CTUIX_Manager;

CTUIX_Node* ctuix_node_create(CTUIX_Element_Type ctuix_element_type, int x, int y, int w, int h, bool focusable, bool input_enabled, char* name, char* value);
CTUIX_Manager* ctuix_manager_create(CTUIX_Node *ctuix_node);
void ctuix_node_free(CTUIX_Node *ctuix_node);

#endif