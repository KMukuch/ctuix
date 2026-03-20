#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

void ctuix_error_show(const char *title, const char *message)
{
    endwin();
    
    fprintf(stderr, "\n========== %s ==========\n", title);
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Press enter to continue...");
    
    getchar();
    
    refresh();
}

void ctuix_error_fatal(const char *msg)
{
    endwin();
    fprintf(stderr, "Fatal error: %s\n", msg);
    fprintf(stderr, "The program will exit.\n");
    exit(EXIT_FAILURE);
}