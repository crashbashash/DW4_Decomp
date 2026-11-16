#ifndef DW4_IGLIGHTINGSTATEATTR_H
#define DW4_IGLIGHTINGSTATEATTR_H

struct igLightingStateAttr;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igLightingStateAttr *igLightingStateAttr_CreateInstance(int allocator);
struct igMetaObject *igLightingStateAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
