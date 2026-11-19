#ifndef DW4_IGVEC2FLIST_H
#define DW4_IGVEC2FLIST_H

/* igVec2fList: the list class's metaobject. */
struct igMemoryPoolView;
struct igMetaObject;
struct igVec2fList;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igVec2fList_metaObject;
struct igVec2fList *igVec2fList_Create(struct igMemoryPoolView *pool);
#ifdef __cplusplus
}
#endif

#endif
