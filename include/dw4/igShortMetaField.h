#ifndef DW4_IGSHORTMETAFIELD_H
#define DW4_IGSHORTMETAFIELD_H

/* igShortMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igShortMetaField_metaObject;
struct igMetaField *igShortMetaField_Create(struct igMemoryPoolView *pool);
void igShortMetaField_SetDefault(struct igMetaField *self, short value);

#ifdef __cplusplus
}
#endif

#endif
