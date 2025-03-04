/**
 * @brief It implements the character module
 *
 * @file character.c
 * @author Javier Pérez
 * @version 2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

struct _Character {
    Id id;                      /*!< Identification number of the character */
    char name[TAM_C];           /*!< Name of the character */
    char gdesc[7];              /*!< Graphic description (6 characters + '\0') */
    int health;                 /*!< Health points of the character */
    Bool friendly;              /*!< Boolean indicating if the character is friendly */
    char message[TAM_C];        /*!< Message associated with the character */
    Id location;                /*!< Location of the character */
};


Character *character_create(Id id) {
    if (id == NO_ID)
        return NULL;

    Character *character = NULL;

    character = (Character *)malloc(sizeof(Character));
    if (!character)
        return NULL;

    character->id = id;
    character->name[0] = '\0';
    character->gdesc[0] = '\0';
    character->health = 3;    
    character->friendly = FALSE;
    character->message[0] = '\0';
    character->location = NO_ID;

    return character;
}

Status character_destroy(Character *character) {
    if (!character)
        return ERROR;

    free(character);
    return OK;
}

Id character_get_id(Character *character) {
    if (!character)
        return NO_ID;

    return character->id;
}

const char *character_get_name(Character *character) {
    if (!character)
        return NULL;

    return character->name;
}

Status character_set_name(Character *character, char *name) {
    if (!character || !name)
        return ERROR;

    if (strlen(name) >= TAM_C)
        return ERROR;

    strcpy(character->name, name);
    return OK;
}

const char *character_get_gdesc(Character *character) {
    if (!character)
        return NULL;

    return character->gdesc;
}

Status character_set_gdesc(Character *character, char *gdesc) {
    if (!character || !gdesc)
        return ERROR;

    if (strlen(gdesc) >= 6)
        return ERROR;

    strcpy(character->gdesc, gdesc);
    return OK;
}

int character_get_health(Character *character) {
    if (!character)
        return -1;

    return character->health;
}

Status character_set_health(Character *character, int health) {
    if (!character || health < 0)
        return ERROR;

    character->health = health;
    return OK;
}

Bool character_is_friendly(Character *character) {
    if (!character)
        return FALSE;

    return character->friendly;
}

Status character_set_friendly(Character *character, Bool friendly) {
    if (!character)
        return ERROR;

    character->friendly = friendly;
    return OK;
}

const char *character_get_message(Character *character) {
    if (!character)
        return NULL;

    return character->message;
}

Status character_set_message(Character *character, char *message) {
    if (!character || !message)
        return ERROR;

    if (strlen(message) >= TAM_C)
        return ERROR;

    strcpy(character->message, message);
    return OK;
}

Id character_get_location(Character *character) {
    if (!character)
        return NO_ID;

    return character->location;
}

Status character_set_location(Character *character, Id location) {
    if (!character || location == NO_ID)
        return ERROR;

    character->location = location;
    return OK;
}

Status character_print(Character *character) {
    if (!character)
        return ERROR;

    fprintf(stdout, "-->character (id: %ld; name: %s; location: %ld; gdesc: %s; health: %d; friendly: %s; message: %s)\n",
            character->id,
            character->name,
            character->location,
            character->gdesc,
            character->health,
            character->friendly ? "TRUE" : "FALSE",
            character->message);

    return OK;
}

