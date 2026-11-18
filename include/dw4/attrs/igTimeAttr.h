#ifndef DW4_IGTIMEATTR_H
#define DW4_IGTIMEATTR_H

struct igTimeAttr;

#ifdef __cplusplus
extern "C" {
#endif

struct igTimeAttr *igTimeAttr_CreateInstance(int allocator);

void igTimeAttr_EnsureRegistered(void);
struct igMetaObject *igTimeAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
