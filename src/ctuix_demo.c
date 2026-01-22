#include <stdio.h>
#include "ctuix_tree.h"
#include "ctuix_utils.h"

#define MAX_FILE_NAME 500

int main()
{
    char buffer[MAX_FILE_NAME];
    scanf("%s", buffer);

    CTUIX_Node *ctuix_root = ctuix_parse(buffer);
    
    return 0;
}