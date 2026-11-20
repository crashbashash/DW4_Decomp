#ifndef DW4_IGMEMORYREFMETAFIELD_H
#define DW4_IGMEMORYREFMETAFIELD_H

/* igMemoryRefMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMemoryRefMetaField;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igMemoryRefMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
