#ifndef DW4_IGVEC2FMETAFIELD_H
#define DW4_IGVEC2FMETAFIELD_H

/* igVec2fMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igVec2fMetaField_metaObject;
struct igMetaField *igVec2fMetaField_CreateInstance(struct igMemoryPoolView *pool);
void igVec2fMetaField_SetDefault(struct igMetaField *self, const float *value);

#ifdef __cplusplus
}
#endif

#endif
