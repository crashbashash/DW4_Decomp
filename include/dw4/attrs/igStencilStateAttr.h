#ifndef DW4_IGSTENCILSTATEATTR_H
#define DW4_IGSTENCILSTATEATTR_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igStencilStateAttr_EnsureRegistered(void);
struct igMetaObject *igStencilStateAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
