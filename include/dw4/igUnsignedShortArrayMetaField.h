#ifndef DW4_IGUNSIGNEDSHORTARRAYMETAFIELD_H
#define DW4_IGUNSIGNEDSHORTARRAYMETAFIELD_H

/* igUnsignedShortArrayMetaField: the metafield class's factory. */
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igUnsignedShortArrayMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
