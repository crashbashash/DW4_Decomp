#ifndef DW4_IGINTARRAYMETAFIELD_H
#define DW4_IGINTARRAYMETAFIELD_H

/* igIntArrayMetaField: the metafield class's factory and default setter. */
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igIntArrayMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
