#include <stdio.h>
#include <ctuix/ctuix_core.h>
#include <ctuix/ctuix_draw.h>
#include <ctuix/ctuix_key.h>
#include <ctuix/ctuix_parse.h>
#include <ctuix/ctuix_utils.h>

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