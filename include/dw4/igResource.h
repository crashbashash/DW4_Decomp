#ifndef DW4_IGRESOURCE_H
#define DW4_IGRESOURCE_H

#include "dw4/igSmartPointer.h"
struct igObject;
struct igResource;
struct igResourceView;
struct igDirectory;

extern "C" {
extern struct igResourceView *g_globalContext;
extern int g_resourceLoaderStackSize;
igSmartPointer<struct igObject> igResource_GetDirectory(void *directory, const char *name);
void igResource_AddAlignment(struct igResource *self, const char *name, int value);
void igResource_StartAsyncLoading(struct igResourceView *self);
void igResource_StopAsyncLoading(struct igResourceView *self);
struct igDirectory *igResource_LoadDirectory(struct igResource *self, const char *path);
unsigned char igResource_IsDirectoryLoaded(struct igResource *self, struct igDirectory *directory);
void igResource_UnloadDirectory(struct igResource *self, const char *name);
}

#endif
