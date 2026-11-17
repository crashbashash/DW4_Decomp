#ifndef DW4_IGSHORTLIST_H
#define DW4_IGSHORTLIST_H

/* igShortList: the list class's metaobject. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igShortList_metaObject;
struct igMetaObject *igShortList_GetOrCreateMetaObject(void);
void igShortList_EnsureRegistered(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
struct igMemoryPoolView;
template <class T> class igTDataList;
extern "C" igTDataList<short> *igShortList_Create(struct igMemoryPoolView *pool);
#endif

#endif
