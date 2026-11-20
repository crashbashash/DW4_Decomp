#ifndef DW4_IGUNSIGNEDCHARMETAFIELD_H
#define DW4_IGUNSIGNEDCHARMETAFIELD_H

/* igUnsignedCharMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igUnsignedCharMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
