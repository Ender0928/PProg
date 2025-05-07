#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link;

/**
 * @brief Creates a new link with the given ID.
 *
 * @param id ID of the link to create.
 * @return Pointer to the newly created link, or NULL if an error occurs.
 */
Link *link_create(Id id);

/**
 * @brief Destroys a link and frees its memory.
 *
 * @param link Pointer to the link to destroy.
 */
void link_destroy(Link *link);

/**
 * @brief Sets the name of a link.
 *
 * @param link Pointer to the link.
 * @param name Name to set for the link.
 * @return Status indicating success or failure.
 */
Status link_set_name(Link *link, const char *name);

/**
 * @brief Retrieves the name of a link.
 *
 * @param link Pointer to the link.
 * @return Pointer to the name of the link, or NULL if not set.
 */
const char *link_get_name(Link *link);

/**
 * @brief Sets the origin ID of a link.
 *
 * @param link Pointer to the link.
 * @param origin ID of the origin to set.
 * @return Status indicating success or failure.
 */
Status link_set_origin(Link *link, Id origin);

/**
 * @brief Retrieves the origin ID of a link.
 *
 * @param link Pointer to the link.
 * @return ID of the origin, or NO_ID if not set.
 */
Id link_get_origin(Link *link);

/**
 * @brief Sets the destination ID of a link.
 *
 * @param link Pointer to the link.
 * @param destination ID of the destination to set.
 * @return Status indicating success or failure.
 */
Status link_set_destination(Link *link, Id destination);

/**
 * @brief Retrieves the destination ID of a link.
 *
 * @param link Pointer to the link.
 * @return ID of the destination, or NO_ID if not set.
 */
Id link_get_destination(Link *link);

/**
 * @brief Sets the direction of a link.
 *
 * @param link Pointer to the link.
 * @param direction Direction to set for the link.
 * @return Status indicating success or failure.
 */
Status link_set_direction(Link *link, Direction direction);

/**
 * @brief Retrieves the direction of a link.
 *
 * @param link Pointer to the link.
 * @return Direction of the link, or NO_DIR if not set.
 */
Direction link_get_direction(Link *link);

/**
 * @brief Sets whether a link is open or closed.
 *
 * @param link Pointer to the link.
 * @param open Boolean indicating if the link is open (TRUE) or closed (FALSE).
 * @return Status indicating success or failure.
 */
Status link_set_open(Link *link, Bool open);

/**
 * @brief Checks if a link is open.
 *
 * @param link Pointer to the link.
 * @return TRUE if the link is open, FALSE otherwise.
 */
Bool link_is_open(Link *link);

/** //TODO test no hecho
 * @brief Retrieves the ID of a link.
 *
 * @param link Pointer to the link.
 * @return ID of the link, or NO_ID if not set.
 */
Id link_get_id(Link *link);

 /**
  * @brief Sets the id of a link.
  *
  * @param link Pointer to the link.
  * @param link_id Id to set on the link
  * @return Status indicating success or failure.
  */
 Status link_set_id(Link *link, Id link_id);
 
/**
 * @brief Prints the details of a link.
 *
 * @param link Pointer to the link.
 * @return Status indicating success or failure.
 */
Status link_print(Link *link);

#endif /* LINK_H */
