#ifndef DW4_IGDOUBLEMETAFIELD_H
#define DW4_IGDOUBLEMETAFIELD_H

/* igDoubleMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igDoubleMetaField_metaObject;
struct igMetaField *igDoubleMetaField_Create(struct igMemoryPoolView *pool);
void igDoubleMetaField_SetDefaultDouble(struct igMetaField *self, double value);

#ifdef __cplusplus
}
#endif

#endif
