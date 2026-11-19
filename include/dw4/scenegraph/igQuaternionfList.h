#ifndef DW4_IGQUATERNIONFLIST_H
#define DW4_IGQUATERNIONFLIST_H

struct igMemoryPoolView;
struct igMetaObject;
struct igQuaternionfList;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igQuaternionfList_GetOrCreateMetaObject(void);
struct igQuaternionfList *igQuaternionfList_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
