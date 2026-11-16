#ifndef DW4_IGDIRENTRY_H
#define DW4_IGDIRENTRY_H

struct igDirEntry;
/* igDirEntry: class registration. */

#ifdef __cplusplus
extern "C" {
#endif

struct igDirEntry *igDirEntry_Destroy(struct igDirEntry *self, short deleteFlag);
extern int g_igDirEntry_vtable[4];

#ifdef __cplusplus
}
#endif

#endif
