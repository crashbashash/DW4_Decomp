#ifndef DW4_IGLONGMETAFIELD_H
#define DW4_IGLONGMETAFIELD_H

/* igLongMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igLongMetaField_metaObject;
void igLongMetaField_Create(int allocator);
void igLongMetaField_SetDefault(void **self, long long value);

#ifdef __cplusplus
}
#endif

#endif
