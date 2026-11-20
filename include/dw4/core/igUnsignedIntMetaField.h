#ifndef DW4_IGUNSIGNEDINTMETAFIELD_H
#define DW4_IGUNSIGNEDINTMETAFIELD_H

/* igUnsignedIntMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igUnsignedIntMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
