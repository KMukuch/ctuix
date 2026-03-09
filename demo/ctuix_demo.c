#include <stdio.h>
#include <ctuix.h>

#define FILEPATH "../data/ctuix_example.xml"

int main()
{   
    ctuix_init();

    CTUIX_Manager *ctuix_manager = ctuix_parse(FILEPATH);
    
    if(ctuix_manager->root_node)
    {
        ctuix_run(ctuix_manager);
    }
    
    ctuix_delete(ctuix_manager);
    
    ctuix_end();
    
    return 0;
}