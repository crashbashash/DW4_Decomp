#ifndef DW4_IGINFOMANAGER_H
#define DW4_IGINFOMANAGER_H

struct igInfoManager;

#ifdef __cplusplus
extern "C" {
#endif
extern int g_igInfoManager_vtable[4];

struct CallbackArray *igInfoManager_Register(void);
/* The destructor: releases the name, and frees the object when `flags` is positive. */
void *igInfoManager_Destroy(struct igInfoManager *manager, short flags);

#ifdef __cplusplus
}
#endif

#endif
