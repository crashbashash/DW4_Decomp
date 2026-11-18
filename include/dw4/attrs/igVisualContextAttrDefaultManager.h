#ifndef DW4_IGVISUALCONTEXTATTRDEFAULTMANAGER_H
#define DW4_IGVISUALCONTEXTATTRDEFAULTMANAGER_H

struct igVisualContextAttrDefaultManager;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igVisualContextAttrDefaultManager *igVisualContextAttrDefaultManager_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
