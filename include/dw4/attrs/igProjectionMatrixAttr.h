#ifndef DW4_IGPROJECTIONMATRIXATTR_H
#define DW4_IGPROJECTIONMATRIXATTR_H

struct igMetaObject;
struct igProjectionMatrixAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igProjectionMatrixAttr_metaObject;
struct igMetaObject *igProjectionMatrixAttr_GetMetaObject(void);
struct igProjectionMatrixAttr *igProjectionMatrixAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
