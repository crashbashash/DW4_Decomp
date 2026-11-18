#ifndef DW4_IGGENERICATTRDEFAULTMANAGER_H
#define DW4_IGGENERICATTRDEFAULTMANAGER_H

struct igGenericAttrDefaultManager;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igGenericAttrDefaultManager *igGenericAttrDefaultManager_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
