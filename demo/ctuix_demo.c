#include <stdio.h>
#include <ctuix.h>

#define FILEPATH1 "../data/ctuix_example_1.xml"
#define FILEPATH2 "../data/ctuix_example_2.xml"
#define FILEPATH3 "../data/ctuix_example_3.xml"
#define FILEPATH4 "../data/ctuix_example.xml"

CTUIX_Event on_click_btn1(CTUIX_Node*, void *user_data);
CTUIX_Event on_click_btn2(CTUIX_Node*, void *user_data);

int main()
{   
    ctuix_init();

    char *files[] = {FILEPATH1, FILEPATH2, FILEPATH3, FILEPATH4};
    CTUIX_Manager *ctuix_manager = ctuix_parse_multiple(files, 4);
    if(!ctuix_manager)
    {
        ctuix_error_show("Error", "No file parsed!");
    }

    if(ctuix_manager)
    {
        ctuix_set_on_click(ctuix_manager, FILEPATH1, "btn1", on_click_btn1, 0);
        ctuix_set_on_click(ctuix_manager, FILEPATH2, "btn2", on_click_btn2, 0);
        ctuix_run(ctuix_manager);
    }
    
    ctuix_delete(ctuix_manager);
    ctuix_end();
    ctuix_cleanup();
    
    return 0;
}

CTUIX_Event on_click_btn1(CTUIX_Node* ctuix_node, void *user_data)
{
    CTUIX_Event event;

    event.ctuix_event_type = CTUIX_EVENT_LOAD;
    event.user_data = FILEPATH2;

    return event;
}

CTUIX_Event on_click_btn2(CTUIX_Node* ctuix_node, void *user_data)
{
    CTUIX_Event event;

    event.ctuix_event_type = CTUIX_EVENT_LOAD;
    event.user_data = FILEPATH3;

    return event;
}