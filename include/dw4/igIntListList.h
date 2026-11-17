#ifndef DW4_IGINTLISTLIST_H
#define DW4_IGINTLISTLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
struct igMetaObject *igIntListList_GetOrCreateMetaObject(void);
void igIntListList_EnsureRegistered(void);
#ifdef __cplusplus
}
#endif

#endif
