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

extern int g_igExternalDirEntry_vtable[4];
void igExternalDirEntry_InitDefaults(struct igDirEntry *self);

#ifdef __cplusplus
}
#endif

#endif
