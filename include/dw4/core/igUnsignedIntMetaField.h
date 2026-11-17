#ifndef DW4_IGUNSIGNEDINTMETAFIELD_H
#define DW4_IGUNSIGNEDINTMETAFIELD_H

/* igUnsignedIntMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igUnsignedIntMetaField_metaObject;
struct igMetaField *igUnsignedIntMetaField_Create(struct igMemoryPoolView *pool);
void igUnsignedIntMetaField_SetDefaultValue(struct igMetaField *self, int value);
int igUnsignedIntMetaField_GetDefaultDescriptor(void);

#ifdef __cplusplus
}
#endif

#endif
