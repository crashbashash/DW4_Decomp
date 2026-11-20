#ifndef DW4_IGUNSIGNEDLONGMETAFIELD_H
#define DW4_IGUNSIGNEDLONGMETAFIELD_H

/* igUnsignedLongMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igUnsignedLongMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
