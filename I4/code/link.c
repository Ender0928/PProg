#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"


struct _Link{
    Id id;
    char name[WORD_SIZE];
    Id origin;
    Id destination;
    Direction direction; 
    Bool open;
};

Link *link_create(Id id) {
    Link *link = NULL;

    if (id == NO_ID) {
        return NULL;
    }

    link = (Link *) malloc(sizeof(Link));
    if (!link) return NULL;
    
    link->id = id;
    link->name[0] = '\0';
    link->origin = NO_ID;
    link->destination = NO_ID;
    link->direction = U;
    link->open = FALSE;

    return link;
}

void link_destroy(Link *link) {
    if (link) {
        free(link);
    }
}

Status link_set_name(Link *link, const char *name) {
    if (!link || !name){
        return ERROR;
    }

    if (!strcpy(link->name, name)) {
        return ERROR;
    }

    return OK;
}

const char *link_get_name(Link *link) {
    if (!link) {
        return NULL;
    }

    return link->name;  
}

Status link_set_origin(Link *link, Id origin) {
    if (!link) return ERROR;

    link->origin = origin;
    return OK;
}

Id link_get_origin(Link *link) {
    if (!link) {
        return NO_ID;
    }

    return link->origin;
}

Status link_set_destination(Link *link, Id destination) {
    if (!link) {
        return ERROR;
    }
    link->destination = destination;
    return OK;
}

Id link_get_destination(Link *link) {
    if (!link) {
        return NO_ID;
    }

    return link->destination;
}

Status link_set_direction(Link *link, Direction direction) {
    if (!link)  {
        return ERROR;
    }
    link->direction = direction;
    return OK;
}

Direction link_get_direction(Link *link) {
    if (!link) {
        return U;
    }
    return link->direction;
}

Status link_set_open(Link *link, Bool open) {
    if (!link) {
        return ERROR;
    }
    link->open = open;
    return OK;
}

Bool link_is_open(Link *link) {
    if (!link) {
        return FALSE;
    }
    return link->open;
}

Id link_get_id(Link *link) {
    if (!link) {
        return NO_ID;
    }
    return link->id;
}

Status link_print(Link *link) {
    if (!link) {
        return ERROR;
    }
    
    printf("Link ID: %ld\n", link->id);
    printf("Name: %s\n", link->name);
    printf("Origin: %ld\n", link->origin);
    printf("Destination: %ld\n", link->destination);
    printf("Direction: %d\n", link->direction);
    printf("Open: %s\n", link->open ? "true" : "false");
    return OK;
}