#ifndef DW4_IGVEC3FLIST_H
#define DW4_IGVEC3FLIST_H

struct igMemoryPoolView;
struct igMetaObject;
struct igVec3fList;

#ifdef __cplusplus
extern "C" {
#endif
struct igMetaObject *igVec3fList_GetOrCreateMetaObject(void);
extern struct igMetaObject *g_igVec3fList_metaObject;
struct igVec3fList *igVec3fList_Create(struct igMemoryPoolView *pool);
#ifdef __cplusplus
}
#endif

#endif
