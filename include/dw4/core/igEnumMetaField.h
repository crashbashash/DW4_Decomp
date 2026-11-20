#ifndef DW4_IGENUMMETAFIELD_H
#define DW4_IGENUMMETAFIELD_H

/* igEnumMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igEnumMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

/* The default arrives by reference, which only C++ can declare. */

#endif
