#ifndef DW4_IGSTRUCTMETAFIELD_H
#define DW4_IGSTRUCTMETAFIELD_H

/* igStructMetaField: the metafield class's factory. */
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igStructMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
