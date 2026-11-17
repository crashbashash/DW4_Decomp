#ifndef DW4_IGUNSIGNEDINTARRAYMETAFIELD_H
#define DW4_IGUNSIGNEDINTARRAYMETAFIELD_H

/* igUnsignedIntArrayMetaField: the metafield class's factory. */
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igUnsignedIntArrayMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
