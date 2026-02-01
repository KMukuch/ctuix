#include <stdio.h>
#include <ctuix/ctuix_parse.h>
#include <ctuix/ctuix_draw.h>
#include <ctuix/ctuix_utils.h>

#define MAX_FILE_NAME 500

int main()
{
    char buffer[MAX_FILE_NAME];
    scanf("%s", buffer);

    CTUIX_Node *ctuix_root = ctuix_parse(buffer);
    
    if(ctuix_root)
    {
        ctuix_init();

        ctuix_run(ctuix_root);

        ctuix_end();
    }
    
    ctuix_delete(ctuix_root);
    
    return 0;
}