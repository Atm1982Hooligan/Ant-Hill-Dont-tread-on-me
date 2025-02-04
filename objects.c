/**
 * 
 * 
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"






typedef struct _Object {
  Id id;                            /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];         /*!< Name of the object */
  char description[WORD_SIZE + 1];  /*!< Description of the object */
    
    
  //char description[WORD_SIZE + 1];  /*!< Vaules in the object(?) */

  Bool relocatable;                 /*!< Whether the object can be moved or not */
};



/**
   Private functions
*/


/**
   Game interface implementation
*/


/**
   Implementation of private functions
*/
