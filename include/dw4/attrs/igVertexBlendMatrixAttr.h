#ifndef DW4_IGVERTEXBLENDMATRIXATTR_H
#define DW4_IGVERTEXBLENDMATRIXATTR_H

struct igMetaObject;
struct igVertexBlendMatrixAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igVertexBlendMatrixAttr_metaObject;
struct igVertexBlendMatrixAttr *igVertexBlendMatrixAttr_Create(struct igMemoryPoolView *pool);

void igVertexBlendMatrixAttr_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
