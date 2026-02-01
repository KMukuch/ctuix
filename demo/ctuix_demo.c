#include <stdio.h>
#include <ctuix/ctuix_parse.h>
#include <ctuix/ctuix_draw.h>
#include <ctuix/ctuix_utils.h>

#define FILEPATH "../data/ctuix_example.xml"

int main()
{   
    ctuix_init();

    CTUIX_Node *ctuix_root = ctuix_parse(FILEPATH);
    
    if(ctuix_root)
    {
        ctuix_run(ctuix_root);
    }
    
    ctuix_delete(ctuix_root);
    
    ctuix_end();
    
    return 0;
}