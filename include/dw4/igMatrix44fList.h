#ifndef DW4_IGMATRIX44FLIST_H
#define DW4_IGMATRIX44FLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
void igMatrix44fList_EnsureRegistered(void);
struct igMetaObject *igMatrix44fList_GetOrCreateMetaObject(void);
#ifdef __cplusplus
}
#endif

#endif
