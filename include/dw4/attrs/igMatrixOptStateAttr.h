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

#ifdef __cplusplus
}
#endif

#endif
