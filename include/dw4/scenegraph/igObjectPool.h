#ifndef DW4_IGOBJECTPOOL_H
#define DW4_IGOBJECTPOOL_H

struct igObject;
struct igObjectPool;

#ifdef __cplusplus
extern "C" {
#endif

void igObjectPool_Grow(struct igObjectPool *pool, struct igObject *(*create)(int allocator));

#ifdef __cplusplus
}
#endif

#endif
