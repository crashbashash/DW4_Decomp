#ifndef DW4_IGSCISSOREXT_H
#define DW4_IGSCISSOREXT_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igScissorExt_EnsureRegistered(void);
struct igMetaObject *igScissorExt_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
