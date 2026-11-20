#ifndef DW4_IGENUMARRAYMETAFIELD_H
#define DW4_IGENUMARRAYMETAFIELD_H

/* igEnumArrayMetaField: the metafield class's factory and default setter. */
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igEnumArrayMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
