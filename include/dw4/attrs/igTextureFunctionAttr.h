#ifndef DW4_IGTEXTUREFUNCTIONATTR_H
#define DW4_IGTEXTUREFUNCTIONATTR_H

struct igTextureFunctionAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igTextureFunctionAttr *igTextureFunctionAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
