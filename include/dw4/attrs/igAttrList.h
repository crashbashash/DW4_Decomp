#ifndef DW4_IGATTRLIST_H
#define DW4_IGATTRLIST_H

struct igMetaObject;
struct igAttrList;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igAttrList_metaObject;
struct igMetaObject *igAttrList_GetOrCreateMetaObject(void);
struct igAttrList *igAttrList_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
