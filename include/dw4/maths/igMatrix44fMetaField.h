#ifndef DW4_IGMATRIX44FMETAFIELD_H
#define DW4_IGMATRIX44FMETAFIELD_H

/* igMatrix44fMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igMatrix44fMetaField_metaObject;
struct igMetaField *igMatrix44fMetaField_CreateInstance(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
