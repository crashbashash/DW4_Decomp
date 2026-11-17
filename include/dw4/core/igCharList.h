#ifndef DW4_IGCHARLIST_H
#define DW4_IGCHARLIST_H

/* igCharList: the list class's metaobject. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igCharList_metaObject;
void igCharList_Create(int pool);
struct igMetaObject *igCharList_GetOrCreateMetaObject(void);
void igCharList_EnsureRegistered(void);
#ifdef __cplusplus
}
#endif

#endif
