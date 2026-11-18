#ifndef DW4_IGALPHASTATEATTR_H
#define DW4_IGALPHASTATEATTR_H

struct igAlphaStateAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igAlphaStateAttr *igAlphaStateAttr_Create(struct igMemoryPoolView *pool);

struct igMetaObject *igAlphaStateAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
