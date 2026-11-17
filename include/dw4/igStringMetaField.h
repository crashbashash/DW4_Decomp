#ifndef DW4_IGSTRINGMETAFIELD_H
#define DW4_IGSTRINGMETAFIELD_H

/* igStringMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igStringMetaField_metaObject;
int igStrcasecmp(const char *s1, const char *s2);
struct igMetaField *igStringMetaField_Create(struct igMemoryPoolView *pool);
void igStringMetaField_SetDefaultText(struct igMetaField *self, const char *text);

#ifdef __cplusplus
}
#endif

#endif
