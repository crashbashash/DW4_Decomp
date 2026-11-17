#ifndef DW4_IGMEMORYPOOL_H
#define DW4_IGMEMORYPOOL_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
void igMemoryPool_EnsureRegistered(void);
struct igMetaObject *igMemoryPool_GetOrCreateMetaObject(void);
#ifdef __cplusplus
}
#endif

#endif
