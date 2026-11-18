#ifndef DW4_IGTEXTUREFUNCTIONATTR_H
#define DW4_IGTEXTUREFUNCTIONATTR_H

struct igTextureFunctionAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igTextureFunctionAttr *igTextureFunctionAttr_Create(struct igMemoryPoolView *pool);

struct igMetaObject *igTextureFunctionAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
