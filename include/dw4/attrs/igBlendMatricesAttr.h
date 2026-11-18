#ifndef DW4_IGBLENDMATRICESATTR_H
#define DW4_IGBLENDMATRICESATTR_H

struct igBlendMatricesAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igBlendMatricesAttr *igBlendMatricesAttr_Create(struct igMemoryPoolView *pool);

void igBlendMatricesAttr_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
