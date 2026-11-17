#ifndef DW4_IGUNSIGNEDCHARMETAFIELD_H
#define DW4_IGUNSIGNEDCHARMETAFIELD_H

/* igUnsignedCharMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igUnsignedCharMetaField_metaObject;
struct igMetaField *igUnsignedCharMetaField_Create(struct igMemoryPoolView *pool);
void igUnsignedCharMetaField_SetDefaultValue(struct igMetaField *self, unsigned char value);
int igUnsignedCharMetaField_GetDefaultDescriptor(void);

#ifdef __cplusplus
}
#endif

#endif
