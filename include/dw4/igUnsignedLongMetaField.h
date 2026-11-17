#ifndef DW4_IGUNSIGNEDLONGMETAFIELD_H
#define DW4_IGUNSIGNEDLONGMETAFIELD_H

/* igUnsignedLongMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igUnsignedLongMetaField_metaObject;
void **igUnsignedLongMetaField_Create(int allocator);
void igUnsignedLongMetaField_SetDefaultValue(void **field, unsigned long long value);

#ifdef __cplusplus
}
#endif

#endif
