#ifndef DW4_IGSTENCILFUNCTIONATTR_H
#define DW4_IGSTENCILFUNCTIONATTR_H

struct igStencilFunctionAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igStencilFunctionAttr *igStencilFunctionAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
