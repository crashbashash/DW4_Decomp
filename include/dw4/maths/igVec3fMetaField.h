#ifndef DW4_IGVEC3FMETAFIELD_H
#define DW4_IGVEC3FMETAFIELD_H

/* igVec3fMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igVec3fMetaField_metaObject;
struct igMetaField *igVec3fMetaField_CreateInstance(struct igMemoryPoolView *pool);
void igVec3fMetaField_SetDefault(struct igMetaField *self, const float *value);
int FUN_00187b10(void);

#ifdef __cplusplus
}
#endif

#endif
