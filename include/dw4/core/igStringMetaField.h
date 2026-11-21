#ifndef DW4_IGSTRINGMETAFIELD_H
#define DW4_IGSTRINGMETAFIELD_H

/* igStringMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

int igStrcasecmp(const char *s1, const char *s2);
struct igMetaField *igStringMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
