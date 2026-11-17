#ifndef DW4_IGUNSIGNEDSHORTMETAFIELD_H
#define DW4_IGUNSIGNEDSHORTMETAFIELD_H

/* igUnsignedShortMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igUnsignedShortMetaField_metaObject;
int igUnsignedShortMetaField_GetDefaultDescriptor(void);
struct igMetaField *igUnsignedShortMetaField_Create(struct igMemoryPoolView *pool);
void igUnsignedShortMetaField_SetDefaultValue(struct igMetaField *self, unsigned short value);

#ifdef __cplusplus
}
#endif

#endif
