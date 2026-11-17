#ifndef DW4_IGCHARMETAFIELD_H
#define DW4_IGCHARMETAFIELD_H

/* igCharMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igCharMetaField_metaObject;
int igCharMetaField_GetDefaultDescriptor(void);
struct igMetaField *igCharMetaField_Create(struct igMemoryPoolView *pool);
void igCharMetaField_SetDefaultValue(struct igMetaField *self, char value);

#ifdef __cplusplus
}
#endif

#endif
