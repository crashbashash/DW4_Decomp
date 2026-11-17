#ifndef DW4_IGSTRINGMETAFIELD_H
#define DW4_IGSTRINGMETAFIELD_H

/* igStringMetaField: the metafield class's metaobject and descriptor calls. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igStringMetaField_metaObject;
int igStrcasecmp(const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif

#endif
