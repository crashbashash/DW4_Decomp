#ifndef DW4_IGINTMETAFIELD_H
#define DW4_IGINTMETAFIELD_H

/* igIntMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igIntMetaField_metaObject;
int igIntMetaField_GetDefaultDescriptor(void);
struct igMetaField *igIntMetaField_Create(struct igMemoryPoolView *pool);
void igIntMetaField_SetDefault(struct igMetaField *self, int value);
void igIntMetaField_EnsureRegistered(void);
struct igMetaObject *igIntMetaField_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
