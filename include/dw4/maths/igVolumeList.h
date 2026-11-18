#ifndef DW4_IGVOLUMELIST_H
#define DW4_IGVOLUMELIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igVolumeList_EnsureRegistered(void);
struct igMetaObject *igVolumeList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
