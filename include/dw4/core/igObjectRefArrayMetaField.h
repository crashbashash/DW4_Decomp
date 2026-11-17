#ifndef DW4_IGOBJECTREFARRAYMETAFIELD_H
#define DW4_IGOBJECTREFARRAYMETAFIELD_H

/* igObjectRefArrayMetaField: the metafield class's factory. */
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igObjectRefArrayMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
