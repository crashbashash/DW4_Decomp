#ifndef DW4_IGINTMETAFIELD_H
#define DW4_IGINTMETAFIELD_H

/* igIntMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igIntMetaField_metaObject;
void igIntMetaField_SetDefault(void **self, int value);
int igIntMetaField_GetDefaultDescriptor(void);

#ifdef __cplusplus
}
#endif

#endif
