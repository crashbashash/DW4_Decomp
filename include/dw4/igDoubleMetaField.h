#ifndef DW4_IGDOUBLEMETAFIELD_H
#define DW4_IGDOUBLEMETAFIELD_H

/* igDoubleMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igDoubleMetaField_metaObject;
void igDoubleMetaField_Create(int pool);
void igDoubleMetaField_SetDefaultDouble(void **field, double value);

#ifdef __cplusplus
}
#endif

#endif
