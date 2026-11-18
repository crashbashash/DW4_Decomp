#ifndef DW4_IGRENDERLISTATTR_H
#define DW4_IGRENDERLISTATTR_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igRenderListAttr_EnsureRegistered(void);
struct igMetaObject *igRenderListAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
