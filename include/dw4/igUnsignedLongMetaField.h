#ifndef DW4_IGUNSIGNEDLONGMETAFIELD_H
#define DW4_IGUNSIGNEDLONGMETAFIELD_H

/* igUnsignedLongMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igUnsignedLongMetaField_metaObject;
struct igMetaField *igUnsignedLongMetaField_Create(struct igMemoryPoolView *pool);
void igUnsignedLongMetaField_SetDefaultValue(struct igMetaField *self, unsigned long long value);

#ifdef __cplusplus
}
#endif

#endif
