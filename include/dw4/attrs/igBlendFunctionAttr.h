#ifndef DW4_IGBLENDFUNCTIONATTR_H
#define DW4_IGBLENDFUNCTIONATTR_H

struct igMetaObject;
struct igBlendFunctionAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igBlendFunctionAttr_GetOrCreateMetaObject(void);
struct igBlendFunctionAttr *igBlendFunctionAttr_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
