#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link;

Link *link_create(Id id);
void link_destroy(Link *link);
Status link_set_name(Link *link, const char *name);
const char *link_get_name(Link *link);
Status link_set_origin(Link *link, Id origin);
Id link_get_origin(Link *link);
Status link_set_destination(Link *link, Id destination);
Id link_get_destination(Link *link);
Status link_set_direction(Link *link, Direction direction);
Direction link_get_direction(Link *link);
Status link_set_open(Link *link, Bool open);
Bool link_is_open(Link *link);
Status link_print(Link *link);

#endif /* LINK_H */
