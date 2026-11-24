#ifndef DW4_IGINFOMANAGER_H
#define DW4_IGINFOMANAGER_H

struct igInfoManager;
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif
extern int g_igInfoManager_vtable[4];

/* The destructor: releases the name, and frees the object when `flags` is positive. */
void *igInfoManager_Destroy(struct igInfoManager *manager, short flags);

#ifdef __cplusplus
}
#endif

#endif
