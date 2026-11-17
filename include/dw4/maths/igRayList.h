#ifndef DW4_IGRAYLIST_H
#define DW4_IGRAYLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
void igRayList_EnsureRegistered(void);
struct igMetaObject *igRayList_GetOrCreateMetaObject(void);
#ifdef __cplusplus
}
#endif

#endif
