#ifndef DW4_IGOBJECTREFMETAFIELD_H
#define DW4_IGOBJECTREFMETAFIELD_H

/* igObjectRefMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igObject;
struct igObjectRefMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igObjectRefMetaField_metaObject;
struct igMetaField *igObjectRefMetaField_Create(struct igMemoryPoolView *pool);
void igObjectRefMetaField_SetDefault(struct igObjectRefMetaField *self, struct igObject *value);

#ifdef __cplusplus
}
#endif

#endif
