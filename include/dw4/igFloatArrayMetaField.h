#ifndef DW4_IGFLOATARRAYMETAFIELD_H
#define DW4_IGFLOATARRAYMETAFIELD_H

/* igFloatArrayMetaField: the metafield class's factory. */
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igFloatArrayMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
