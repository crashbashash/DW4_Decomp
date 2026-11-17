#ifndef DW4_IGUNSIGNEDINTLIST_H
#define DW4_IGUNSIGNEDINTLIST_H

/* igUnsignedIntList: the list class's registration. */
struct CallbackArray;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igUnsignedIntList_GetPublishedMetaObject(void);
void igUnsignedIntList_EnsureRegistered(void);
struct igMetaObject *igUnsignedIntList_GetOrCreateMetaObject(void);
struct CallbackArray *igUnsignedIntList_Register(void);
extern struct igMetaObject *g_igUnsignedIntList_metaObject;

#ifdef __cplusplus
}
#endif

#endif
