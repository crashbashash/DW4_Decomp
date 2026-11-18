#ifndef DW4_IGTRANSFORM_H
#define DW4_IGTRANSFORM_H

struct CallbackArray;
struct igMetaObject;
struct igTransform;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igTransform_metaObject;
struct igTransform *igTransform_CreateInstance(int allocator);
struct igMetaObject *igTransform_GetOrCreateMetaObject(void);
struct CallbackArray *igTransform_Register(void);
extern int g_igTransform_vtable[4];

struct igMetaObject *igTransform_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
