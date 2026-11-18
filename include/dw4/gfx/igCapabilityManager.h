#ifndef DW4_IGCAPABILITYMANAGER_H
#define DW4_IGCAPABILITYMANAGER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igCapabilityManager_EnsureRegistered(void);
struct igMetaObject *igCapabilityManager_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
