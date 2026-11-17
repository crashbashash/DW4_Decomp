#ifndef DW4_IGFLOATMETAFIELD_H
#define DW4_IGFLOATMETAFIELD_H

/* igFloatMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igFloatMetaField_metaObject;
struct igMetaField *igFloatMetaField_Create(struct igMemoryPoolView *pool);
void igFloatMetaField_SetDefault(struct igMetaField *self, float value);
int igFloatMetaField_GetDefaultDescriptor(void);

#ifdef __cplusplus
}
#endif

#endif
