#ifndef DW4_IGRAWREFMETAFIELD_H
#define DW4_IGRAWREFMETAFIELD_H

/* igRawRefMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igRawRefMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
