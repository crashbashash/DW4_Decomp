#ifndef DW4_IGMEMORYREFMETAFIELD_H
#define DW4_IGMEMORYREFMETAFIELD_H

/* igMemoryRefMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igMemoryRefMetaField_metaObject;
struct igMetaField *igMemoryRefMetaField_Create(struct igMemoryPoolView *pool);
void igMemoryRefMetaField_SetDefaultWord(struct igMetaField *self, int value);

#ifdef __cplusplus
}
#endif

#endif
