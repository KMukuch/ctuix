#ifndef CTUIX_H
#define CTUIX_H

#define CTUIX_VERSION_MAJOR 0
#define CTUIX_VERSION_MINOR 0
#define CTUIX_VERSION_PATCH 0

typedef enum
{
    CTUIX_EVENT_TYPE_NONE,
    CTUIX_EVENT_TYPE_QUIT,
    CTUIX_EVENT_TYPE_LOAD,
    CTUIX_EVENT_TYPE_UPDATE
} CTUIX_Event_Type;

typedef struct CTUIX_Event
{
    CTUIX_Event_Type ctuix_event_type;
    void *user_data;
} CTUIX_Event;

typedef struct CTUIX_Node CTUIX_Node;
typedef struct CTUIX_Manager CTUIX_Manager;

/*
 * Function prototypes
 */

void ctuix_init(void);
int ctuix_run(CTUIX_Manager *ctuix_manager);
void ctuix_end(void);

CTUIX_Manager* ctuix_parse(char *file_path);
CTUIX_Manager* ctuix_parse_multiple(char **file_path, int count);
void ctuix_delete(CTUIX_Manager *ctuix_manager);
void ctuix_cleanup();

void ctuix_set_on_click(CTUIX_Manager *ctuix_manager, char *file_path, char *ctuix_node_id, CTUIX_Event (*on_click)(CTUIX_Node*, void *user_data), void *user_data);

void ctuix_error_show(const char *title, const char *message);

#endif