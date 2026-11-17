#ifndef DW4_IGCHARMETAFIELD_H
#define DW4_IGCHARMETAFIELD_H

/* igCharMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igCharMetaField_metaObject;
int igCharMetaField_GetDefaultDescriptor(void);

#ifdef __cplusplus
}
#endif

#endif
