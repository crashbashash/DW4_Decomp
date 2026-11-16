#ifndef DW4_IGATTRSET_H
#define DW4_IGATTRSET_H

struct igAttrSet;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igAttrSet *igAttrSet_CreateInstance(int allocator);
struct igMetaObject *igAttrSet_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
