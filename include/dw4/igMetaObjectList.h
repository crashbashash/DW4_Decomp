#ifndef DW4_IGMETAOBJECTLIST_H
#define DW4_IGMETAOBJECTLIST_H

/* igMetaObjectList: the list class's registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igMetaObjectList_GetOrCreateMetaObject(void);
void igMetaObjectList_EnsureRegistered(void);
void *igMetaObjectList_Create(int pool);

#ifdef __cplusplus
}
#endif

#endif
