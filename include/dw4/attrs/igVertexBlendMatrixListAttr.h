#ifndef DW4_IGVERTEXBLENDMATRIXLISTATTR_H
#define DW4_IGVERTEXBLENDMATRIXLISTATTR_H

struct igMetaField;
struct igMetaObject;
struct igVertexBlendMatrixListAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igVertexBlendMatrixListAttr_metaObject;
extern struct igMetaField *g_igVertexBlendMatrixListAttr_skeletonTransformMetaField;
extern struct igMetaField *g_igVertexBlendMatrixListAttr_skeletonInverseTransformMetaField;
struct igVertexBlendMatrixListAttr *igVertexBlendMatrixListAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
