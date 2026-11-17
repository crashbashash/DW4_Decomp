#ifndef DW4_IGINTERFACEMANAGER_H
#define DW4_IGINTERFACEMANAGER_H

struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

struct CallbackArray *igInterfaceManager_Register(void);
struct igMetaObject *igInterfaceManager_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
