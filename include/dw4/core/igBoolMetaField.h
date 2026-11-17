#ifndef DW4_IGBOOLMETAFIELD_H
#define DW4_IGBOOLMETAFIELD_H

/* igBoolMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igBoolMetaField_metaObject;
struct igMetaField *igBoolMetaField_Create(struct igMemoryPoolView *pool);
void igBoolMetaField_SetDefaultValue(struct igMetaField *self, char value);

#ifdef __cplusplus
}
#endif

#endif
