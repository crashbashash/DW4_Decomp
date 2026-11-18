#ifndef DW4_IGALPHAFUNCTIONATTR_H
#define DW4_IGALPHAFUNCTIONATTR_H

struct igAlphaFunctionAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igAlphaFunctionAttr *igAlphaFunctionAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
