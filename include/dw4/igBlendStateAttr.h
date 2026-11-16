#ifndef DW4_IGBLENDSTATEATTR_H
#define DW4_IGBLENDSTATEATTR_H

struct igBlendStateAttr;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igBlendStateAttr *igBlendStateAttr_CreateInstance(int allocator);
struct igMetaObject *igBlendStateAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
