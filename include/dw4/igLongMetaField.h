#ifndef DW4_IGLONGMETAFIELD_H
#define DW4_IGLONGMETAFIELD_H

/* igLongMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igLongMetaField_metaObject;
struct igMetaField *igLongMetaField_Create(struct igMemoryPoolView *pool);
void igLongMetaField_SetDefault(struct igMetaField *self, long long value);

#ifdef __cplusplus
}
#endif

#endif
