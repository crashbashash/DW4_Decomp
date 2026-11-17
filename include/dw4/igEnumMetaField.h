#ifndef DW4_IGENUMMETAFIELD_H
#define DW4_IGENUMMETAFIELD_H

/* igEnumMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igEnumMetaField_metaObject;
void **igEnumMetaField_Create(int pool);

#ifdef __cplusplus
}
#endif

#endif
