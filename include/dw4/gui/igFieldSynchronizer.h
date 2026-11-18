#ifndef DW4_IGFIELDSYNCHRONIZER_H
#define DW4_IGFIELDSYNCHRONIZER_H

struct igFieldSynchronizer;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igFieldSynchronizer *igFieldSynchronizer_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
