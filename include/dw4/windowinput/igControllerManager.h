#ifndef DW4_IGCONTROLLERMANAGER_H
#define DW4_IGCONTROLLERMANAGER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igControllerManager_EnsureRegistered(void);
struct igMetaObject *igControllerManager_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
