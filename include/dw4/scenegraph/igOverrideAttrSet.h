#ifndef DW4_IGOVERRIDEATTRSET_H
#define DW4_IGOVERRIDEATTRSET_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igOverrideAttrSet_EnsureRegistered(void);
struct igMetaObject *igOverrideAttrSet_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
