#ifndef DW4_IGCLIPPINGSTATEATTR_H
#define DW4_IGCLIPPINGSTATEATTR_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igClippingStateAttr_EnsureRegistered(void);
struct igMetaObject *igClippingStateAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
