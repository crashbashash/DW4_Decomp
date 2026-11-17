#ifndef DW4_IGIGBFILE_H
#define DW4_IGIGBFILE_H

/* igIGBFile: class registration. */

#ifdef __cplusplus
extern "C" {
#endif

int igIGBFile_GetOrCreateMetaObject(void);
void igIGBFile_EnsureRegistered(void);
void *igIGBFile_Create(int pool);

#ifdef __cplusplus
}
#endif

#endif
