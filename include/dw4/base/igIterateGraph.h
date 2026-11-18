#ifndef DW4_IGITERATEGRAPH_H
#define DW4_IGITERATEGRAPH_H

struct igMetaObject;

struct igObject;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif
struct igObject *igIterateGraph_Create(struct igMemoryPoolView *pool);

struct igMetaObject *igIterateGraph_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
