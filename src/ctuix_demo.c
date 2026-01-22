#include <stdio.h>
#include "ctuix_tree.h"
#include "ctuix_utils.h"

#define MAX_FILE_NAME 500

int main()
{
    char buffer[MAX_FILE_NAME];
    scanf("%s", buffer);

    CTUIX_Node *ctuix_root = ctuix_parse(buffer);
    
    if(ctuix_root)
    {
        printf("The UI Tree was created successfully!\n");
    }
    
    ctuix_delete(ctuix_root);
    
    return 0;
}