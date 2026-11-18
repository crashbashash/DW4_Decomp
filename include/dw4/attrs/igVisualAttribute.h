#ifndef DW4_IGVISUALATTRIBUTE_H
#define DW4_IGVISUALATTRIBUTE_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igVisualAttribute_EnsureRegistered(void);
struct igMetaObject *igVisualAttribute_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
