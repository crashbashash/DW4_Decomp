#ifndef DW4_IGTRANSFORM_H
#define DW4_IGTRANSFORM_H

struct igMetaObject;
struct igTransform;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igTransform_metaObject;
struct igTransform *igTransform_CreateInstance(int allocator);
struct igMetaObject *igTransform_GetOrCreateMetaObject(void);
void igTransform_Register(void);

#ifdef __cplusplus
}
#endif

#endif
