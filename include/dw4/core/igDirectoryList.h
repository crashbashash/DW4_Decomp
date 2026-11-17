#ifndef DW4_IGDIRECTORYLIST_H
#define DW4_IGDIRECTORYLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
struct igMetaObject *igDirectoryList_GetOrCreateMetaObject(void);
void igDirectoryList_EnsureRegistered(void);
#ifdef __cplusplus
}
#endif

#endif
