#ifndef DW4_IGVISUALCONTEXTCAPABILITYMANAGER_H
#define DW4_IGVISUALCONTEXTCAPABILITYMANAGER_H

struct igObject;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igObject *igVisualContextCapabilityManager_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
