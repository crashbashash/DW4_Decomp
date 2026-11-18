#ifndef DW4_IGDEFAULTASPECT_H
#define DW4_IGDEFAULTASPECT_H

#ifdef __cplusplus
extern "C" {
#endif

void igDefaultAspect_EnsureRegistered(void);

struct igMetaObject *igDefaultAspect_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
