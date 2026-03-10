#ifndef CTUIX_H
#define CTUIX_H

#define CTUIX_VERSION_MAJOR 0
#define CTUIX_VERSION_MINOR 0
#define CTUIX_VERSION_PATCH 0

typedef struct CTUIX_Node CTUIX_Node;
typedef struct CTUIX_Manager CTUIX_Manager;

void ctuix_init();
int ctuix_run(CTUIX_Manager *ctuix_manager);
void ctuix_end();

CTUIX_Manager* ctuix_parse(char *file_path);
void ctuix_delete(CTUIX_Manager *ctuix_manager);

#endif