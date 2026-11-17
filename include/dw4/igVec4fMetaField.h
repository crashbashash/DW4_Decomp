#ifndef DW4_IGVEC4FMETAFIELD_H
#define DW4_IGVEC4FMETAFIELD_H

/* igVec4fMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igVec4fMetaField_metaObject;
struct igMetaField *igVec4fMetaField_CreateInstance(struct igMemoryPoolView *pool);
void igVec4fMetaField_SetDefault(struct igMetaField *self, const float *value);

#ifdef __cplusplus
}
#endif

#endif
