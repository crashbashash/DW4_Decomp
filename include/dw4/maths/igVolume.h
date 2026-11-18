#ifndef DW4_IGVOLUME_H
#define DW4_IGVOLUME_H


#ifdef __cplusplus
extern "C" {
#endif
void igVolume_ExtendBy(void **volume, void **other);
void igVolume_EnsureRegistered(void);
struct igMetaObject *igVolume_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
