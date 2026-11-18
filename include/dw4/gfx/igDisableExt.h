#ifndef DW4_IGDISABLEEXT_H
#define DW4_IGDISABLEEXT_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igDisableExt_EnsureRegistered(void);
struct igMetaObject *igDisableExt_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
