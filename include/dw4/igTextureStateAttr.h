#ifndef DW4_IGTEXTURESTATEATTR_H
#define DW4_IGTEXTURESTATEATTR_H

struct igMetaObject;
struct igTextureStateAttr;

#ifdef __cplusplus
extern "C" {
#endif

struct igTextureStateAttr *igTextureStateAttr_CreateInstance(int allocator);
struct igMetaObject *igTextureStateAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
