#ifndef DW4_IGBLENDEQUATIONEXT_H
#define DW4_IGBLENDEQUATIONEXT_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igBlendEquationExt_EnsureRegistered(void);
struct igMetaObject *igBlendEquationExt_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
