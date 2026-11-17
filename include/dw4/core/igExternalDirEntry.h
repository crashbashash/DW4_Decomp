#ifndef DW4_IGEXTERNALDIRENTRY_H
#define DW4_IGEXTERNALDIRENTRY_H

struct igDirEntry;
struct igExternalDirEntry;
struct CallbackArray;
struct igMetaObject;

/* igExternalDirEntry: class registration. */

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igExternalDirEntry_metaObject;

extern int g_igExternalDirEntry_vtable[4];
struct CallbackArray *igExternalDirEntry_Register(void);
void igExternalDirEntry_InitDefaults(struct igDirEntry *self);
void igExternalDirEntry_SetDirectoryName(struct igExternalDirEntry *self, int name);

#ifdef __cplusplus
}
#endif

#endif
