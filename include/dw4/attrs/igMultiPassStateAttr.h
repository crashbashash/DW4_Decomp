#ifndef DW4_IGMULTIPASSSTATEATTR_H
#define DW4_IGMULTIPASSSTATEATTR_H

struct igMultiPassStateAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igMultiPassStateAttr *igMultiPassStateAttr_Create(struct igMemoryPoolView *pool);

void igMultiPassStateAttr_EnsureRegistered(void);
struct igMetaObject *igMultiPassStateAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
