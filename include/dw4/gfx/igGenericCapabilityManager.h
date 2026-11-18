#ifndef DW4_IGGENERICCAPABILITYMANAGER_H
#define DW4_IGGENERICCAPABILITYMANAGER_H

struct igObject;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igObject *igGenericCapabilityManager_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
