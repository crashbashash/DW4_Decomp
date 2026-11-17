#ifndef DW4_IGADXAFSFILELIST_H
#define DW4_IGADXAFSFILELIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igAdxAfsFileList_EnsureRegistered(void);
struct igMetaObject *igAdxAfsFileList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
