#ifndef DW4_IGBOOLMETAFIELD_H
#define DW4_IGBOOLMETAFIELD_H

/* igBoolMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igBoolMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
