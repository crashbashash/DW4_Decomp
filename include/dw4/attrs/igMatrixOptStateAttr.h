#ifndef DW4_IGMATRIXOPTSTATEATTR_H
#define DW4_IGMATRIXOPTSTATEATTR_H

struct igMetaObject;
struct igMatrixOptStateAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igMatrixOptStateAttr_metaObject;
struct igMatrixOptStateAttr *igMatrixOptStateAttr_Create(struct igMemoryPoolView *pool);

void igMatrixOptStateAttr_EnsureRegistered(void);
struct igMetaObject *igMatrixOptStateAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
