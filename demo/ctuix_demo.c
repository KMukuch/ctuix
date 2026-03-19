#include <stdio.h>
#include <ctuix.h>

#define FILEPATH1 "../data/ctuix_example_1.xml"
#define FILEPATH2 "../data/ctuix_example_2.xml"
#define FILEPATH3 "../data/ctuix_example_3.xml"

CTUIX_Event on_click_btn(CTUIX_Node*, void *user_data);

int main()
{   
    ctuix_init();

    char *files[] = {FILEPATH1, FILEPATH2, FILEPATH3};
    CTUIX_Manager *ctuix_manager = ctuix_parse_multiple(files, 3);

    if(ctuix_manager)
    {
        ctuix_set_on_click(ctuix_manager, FILEPATH1, "btn", on_click_btn, 0);

        ctuix_run(ctuix_manager);
    }
    
    ctuix_delete(ctuix_manager);
    
    ctuix_end();
    
    return 0;
}

CTUIX_Event on_click_btn(CTUIX_Node* ctuix_node, void *user_data)
{
    CTUIX_Event event;

    event.ctuix_event_type = CTUIX_EVENT_LOAD;
    event.user_data = FILEPATH2;

    return event;
}