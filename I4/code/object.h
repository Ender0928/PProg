/**
 * @brief It defines the object interface
 *
 * @file object.h
 * @author Javier and Rubén
 * @version 1.0
 */

 #ifndef OBJECT_H
 #define OBJECT_H
 
 #include "types.h"
 
 #define O 45
 #define TAM 256
 
 typedef struct _Object Object;
 
 /**
   * @brief It creates a new object
   * @author Javier and Rubén
   *
   * object_create allocates memory for a new object
   *  and initializes its members
   * @param id the identification number for the new object
   * @return a new object, initialized
   */
 Object* object_create (Id id);
 
 /**
   * @brief It destroys an object
   * @author Javier and Rubén
   *
   * object_destroy frees the previous memory allocation 
   *  for an object
   * @param object a pointer to the object that must be destroyed  
   * @return OK, if everything goes well or ERROR if there was some mistake
   */
 Status object_destroy(Object* object);
 
 
 /**
   * @brief It gets the id of an object
   * @author Javier and Rubén
   * 
   * @param object a pointer to the object  
   * @return the id of object
   */
 Id object_get_id(Object* object);
 
 /**
   * @brief It sets the id of an object
   * @author Javier and Rubén
   * 
   * @param object a pointer to the object  
   * @return the id of object
   */
 Status object_set_id(Object* object, Id id);
 
 /**
   * @brief It sets the name of an object
   * @author Javier and Rubén
   * 
   * @param space a pointer to the object
   * @param name a string with the name to store
   * @return OK, if everything goes well or ERROR if there was some mistake 
   */
 Status object_set_name(Object* object, char* name);
 
 /**
   * @brief It gets the name of an object
   * @author Javier and Rubén
   * 
   * @param object a pointer to the object
   * @return  a string with the name of the object
   */
 char * object_get_name(Object* object);
 
 /**
   * @brief It sets the description of an object
   * @param object a pointer to the object
   * @param name a string to the object's description to store
   * @return OK, if everything goes well or ERROR if there was some mistake
   */
 Status object_set_description(Object* object, char *name);
 
 /**
   * @brief It gets the description of an object
   * @param object a pointer to the object
   * @return a string with the description of the object
   */
 char * object_get_description(Object* object);
 
 /**
  * @brief Gets the health of an object
  * @param object pointer to the object
  * @return the health of the object or -1 if error
  */
 int object_get_health(Object *object);
 
 /**
  * @brief Sets the health of an object
  * @param object pointer to the object
  * @param health the new health value
  * @return OK if successful, ERROR otherwise
  */
 Status object_set_health(Object *object, int health);
 
 /**
  * @brief Gets the movable variable of an object
  * @param object pointer to the object
  * @return TRUE if the object is movable, FALSE otherwise
  */
 Bool object_get_movable(Object *object);
 
 /**
  * @brief Sets the movable variable of an object
  * @param object pointer to the object
  * @param movable the new movable value
  * @return OK if successful, ERROR otherwise
  */
 Status object_set_movable(Object *object, Bool movable);
 
 /**
  * @brief Gets the dependency of an object
  * @param object pointer to the object
  * @return Id of the dependent object or NO_ID in case of ERROR
  */
 Id object_get_dependency(Object *object);
 
 /**
  * @brief Sets the dependency of an object
  * @param object pointer to the object
  * @param dependency the id of the dependent object
  * @return OK if successful, ERROR otherwise
  */
 Status object_set_dependency(Object *object, Id dependency);
 
 /**
  * @brief Gets the open ID of an object
  * @param object pointer to the object
  * @return Id of the link that can be opened with this object or NO_ID otherwise.
  */
 Id object_get_open(Object *object);
 
 /**
  * @brief Sets the open ID of an object
  * @param object pointer to the object
  * @param open the id of link to be opened by this object
  * @return OK if successful, ERROR otherwise
  */
 Status object_set_open(Object *object, Id open);
 
 /**
   * @brief It prints the information of an object
   * @param object a pointer to the object
   * @return OK, if everything goes well or ERROR if there was some mistake
   */
  Status object_print(Object* object);
 
 #endif
 