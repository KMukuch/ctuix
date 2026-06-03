#ifndef CTUIX_EVENT_H
#define CTUIX_EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

typedef enum
{
    CTUIX_EVENT_TYPE_NONE,
    CTUIX_EVENT_TYPE_QUIT,
    CTUIX_EVENT_TYPE_LOAD,
    CTUIX_EVENT_TYPE_UPDATE
} CTUIX_Event_Type;

typedef struct CTUIX_Event
{
    CTUIX_Event_Type ctuix_event_type;

    char *message;
    
    int event_counter;

    void *user_data;
} CTUIX_Event;

#endif