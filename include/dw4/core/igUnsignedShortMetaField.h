#ifndef DW4_IGUNSIGNEDSHORTMETAFIELD_H
#define DW4_IGUNSIGNEDSHORTMETAFIELD_H

/* igUnsignedShortMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igUnsignedShortMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
