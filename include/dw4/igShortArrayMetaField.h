#ifndef DW4_IGSHORTARRAYMETAFIELD_H
#define DW4_IGSHORTARRAYMETAFIELD_H

/* igShortArrayMetaField: the metafield class's factory. */
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igShortArrayMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
