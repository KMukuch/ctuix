#ifndef CTUIX_H
#define CTUIX_H

#define CTUIX_VERSION_MAJOR 0
#define CTUIX_VERSION_MINOR 0
#define CTUIX_VERSION_PATCH 0

typedef struct CTUIX_Node CTUIX_Node;
typedef struct CTUIX_Manager CTUIX_Manager;

/// @brief Initilizing CTUIX and NCURSES library
/// @param void
void ctuix_init(void);

/// @brief Running the CTUIX core
/// @param ctuix_manager 
/// @return If no error, returns 1
int ctuix_run(CTUIX_Manager *ctuix_manager);

/// @brief End CTUIX and NCURSES library
/// @param void
void ctuix_end(void);

/// @brief Parse an XML file
/// @param file_path 
/// @return If no error, returns an allocated memory for a new CTUIX_Manager
CTUIX_Manager* ctuix_parse(char *file_path);
/// @brief Parse multiple XML files
/// @param file_path 
/// @param count 
/// @return If no error, returns an allocated memory for list of new CTUIX_Managers
CTUIX_Manager* ctuix_parse_multiple(char **file_path, int count);

/// @brief 
/// @param ctuix_node 
/// @param ctuix_node_id 
/// @return 
CTUIX_Node* ctuix_find_node_by_id(CTUIX_Node *ctuix_node, char *ctuix_node_id);

/// @brief 
/// @param ctuix_manager
/// @param file_path 
/// @return 
CTUIX_Manager* ctuix_find_manager_by_path(CTUIX_Manager *ctuix_manager, char *file_path);

/// @brief 
/// @param ctuix_manager 
/// @param ctuix_node_id 
/// @param event_handler 
void ctuix_button_set_event_handler(CTUIX_Manager *ctuix_manager, char *ctuix_node_id, void (*event_handler)(void));

/// @brief Free memory from CTUIX library
/// @param ctuix_manager 
void ctuix_delete(CTUIX_Manager *ctuix_manager);

/// @brief Free memory from libxml after parsing
void ctuix_cleanup();

/// @brief 
/// @param title 
/// @param message 
void ctuix_error_show(const char *title, const char *message);

#endif