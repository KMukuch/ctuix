#include <stdio.h>
#include <ctuix.h>

// #define FILEPATH1 "../data/ctuix_example_1.xml"
#define FILEPATH2 "../data/ctuix_example_2.xml"
// #define FILEPATH3 "../data/ctuix_example_3.xml"

int main()
{
    ctuix_init();

    // char *files[] = {FILEPATH1, FILEPATH2, FILEPATH3, FILEPATH4};
    CTUIX_Manager *ctuix_manager = ctuix_parse(FILEPATH2);
    if(!ctuix_manager)
    {
        ctuix_error_show("Error", "No file parsed!");
    }

    if(ctuix_manager)
    {
        ctuix_run(ctuix_manager);
    }
    
    ctuix_delete(ctuix_manager);
    ctuix_end();
    ctuix_cleanup();
    
    return 0;
}