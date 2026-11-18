#ifndef DW4_IGTEXTUREBINDATTR_H
#define DW4_IGTEXTUREBINDATTR_H

struct igMetaObject;
struct igTextureBindAttr;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igTextureBindAttr_metaObject;
struct igTextureBindAttr *igTextureBindAttr_CreateInstance(int allocator);
struct igMetaObject *igTextureBindAttr_GetMetaObject(void);

struct igMetaObject *igTextureBindAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
