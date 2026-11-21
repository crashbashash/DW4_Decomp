#ifndef DW4_IGCOMPOUNDMETAFIELD_H
#define DW4_IGCOMPOUNDMETAFIELD_H

/* igCompoundMetaField: the metafield class's metaobject and descriptor calls. */
struct CallbackArray;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern int g_igCompoundMetaField_vtable[4];

struct igMetaObject *igCompoundMetaField_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
