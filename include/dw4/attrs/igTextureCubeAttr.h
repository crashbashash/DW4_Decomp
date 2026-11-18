#ifndef DW4_IGTEXTURECUBEATTR_H
#define DW4_IGTEXTURECUBEATTR_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igTextureCubeAttr_EnsureRegistered(void);
struct igMetaObject *igTextureCubeAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
