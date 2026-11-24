#ifndef DW4_IGDEPENDENCYORDEREDLIST_H
#define DW4_IGDEPENDENCYORDEREDLIST_H

/* igDependencyOrderedList: a list of objects kept in an order that honours (dependent, dependency)
 * pairs, with named check points to order against. */
#include "dw4/core/igResult.h"
struct igDependencyOrderedList;
struct igObject;
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igDependencyOrderedList_GetPublishedMetaObject(void);
/* Removes every pair naming `object`. */
/* Releases and removes `object` from the ordered objects. */

#ifdef __cplusplus
}
#endif

#endif
