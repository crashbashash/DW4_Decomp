#ifndef DW4_IGTEXGENMATRIXATTR_H
#define DW4_IGTEXGENMATRIXATTR_H

struct igTexGenMatrixAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igTexGenMatrixAttr *igTexGenMatrixAttr_Create(struct igMemoryPoolView *pool);

void igTexGenMatrixAttr_EnsureRegistered(void);
struct igMetaObject *igTexGenMatrixAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
