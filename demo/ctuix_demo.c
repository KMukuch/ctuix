#include <stdio.h>
#include <ctuix.h>

#define FILEPATH1 "../data/ctuix_example_main.xml"
#define FILEPATH2 "../data/ctuix_example_menu.xml"

CTUIX_Event on_click_btn(CTUIX_Node*, void *user_data);

int main()
{   
    ctuix_init();

    CTUIX_Manager *ctuix_manager = ctuix_parse(FILEPATH1);

    if(ctuix_manager)
    {
        ctuix_set_on_click(ctuix_manager, "btn", on_click_btn, 0);

        ctuix_run(ctuix_manager);
    }
    
    ctuix_delete(ctuix_manager);
    
    ctuix_end();
    
    return 0;
}

CTUIX_Event on_click_btn(CTUIX_Node* ctuix_node, void *user_data)
{
    CTUIX_Manager *new_manager = ctuix_parse(FILEPATH2);
    CTUIX_Event event;
    if(new_manager)
    {
        event.ctuix_event_type = CTUIX_EVENT_LOAD;
        event.user_data = new_manager;
    }
    return event;
}