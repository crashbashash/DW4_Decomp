#ifndef DW4_IGDEPENDENCYORDEREDLIST_H
#define DW4_IGDEPENDENCYORDEREDLIST_H

/* igDependencyOrderedList: a list of objects kept in an order that honours (dependent, dependency)
 * pairs, with named check points to order against. */
#include "dw4/igResult.h"
struct igDependencyOrderedList;
struct igObject;
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

extern int g_igDependencyOrderedList_vtable[4];
extern struct igMetaObject *g_igDependencyOrderedList_metaObject;
struct CallbackArray *igDependencyOrderedList_Register(void);
struct igMetaObject *igDependencyOrderedList_GetPublishedMetaObject(void);
void igDependencyOrderedList_AddDependency(struct igDependencyOrderedList *self, void *dependent, void *dependency);
igResult igDependencyOrderedList_RemoveDependency(struct igDependencyOrderedList *self, void *dependent, void *dependency);
/* Removes every pair naming `object`. */
void igDependencyOrderedList_RemoveDependencies(struct igDependencyOrderedList *self, void *object);
void igDependencyOrderedList_AddCheckPoint(struct igDependencyOrderedList *self, const char *name);
/* Releases and removes `object` from the ordered objects. */
igResult igObjectList_RemoveRetained(struct igDependencyOrderedList *list, struct igObject *object);

#ifdef __cplusplus
}
#endif

#endif
