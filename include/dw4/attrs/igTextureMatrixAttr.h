#ifndef DW4_IGTEXTUREMATRIXATTR_H
#define DW4_IGTEXTUREMATRIXATTR_H

struct igMetaObject;
struct igTextureMatrixAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igTextureMatrixAttr_metaObject;
struct igTextureMatrixAttr *igTextureMatrixAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
