#ifndef DW4_IGFLOATMETAFIELD_H
#define DW4_IGFLOATMETAFIELD_H

/* igFloatMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igFloatMetaField_metaObject;
void igFloatMetaField_Create(int allocator);
void igFloatMetaField_SetDefault(void **self, float value);

#ifdef __cplusplus
}
#endif

#endif
