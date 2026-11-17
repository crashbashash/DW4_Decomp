#ifndef DW4_IGUNSIGNEDCHARMETAFIELD_H
#define DW4_IGUNSIGNEDCHARMETAFIELD_H

/* igUnsignedCharMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igUnsignedCharMetaField_metaObject;
void igUnsignedCharMetaField_Create(int pool);
void igUnsignedCharMetaField_SetDefaultValue(void **self, char value);

#ifdef __cplusplus
}
#endif

#endif
