#ifndef DW4_IGVEC4UCLIST_H
#define DW4_IGVEC4UCLIST_H

/* igVec4ucList: the list class's metaobject. */
struct igMemoryPoolView;
struct igMetaObject;
struct igVec4ucList;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igVec4ucList_metaObject;
struct igVec4ucList *igVec4ucList_Create(struct igMemoryPoolView *pool);
#ifdef __cplusplus
}
#endif

#endif
