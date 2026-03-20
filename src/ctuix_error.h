#ifndef CTUIX_H
#define CTUIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "ctuix_tree.h"

void ctuix_error_show(const char *title, const char *message);
void ctuix_error_fatal(const char *msg);

#endif