#ifndef DW4_IGMETAOBJECTLISTLIST_H
#define DW4_IGMETAOBJECTLISTLIST_H

/* igMetaObjectListList: the list class's registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igMetaObjectListList_GetOrCreateMetaObject(void);
void igMetaObjectListList_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
