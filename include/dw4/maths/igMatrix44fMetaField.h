#ifndef DW4_IGMATRIX44FMETAFIELD_H
#define DW4_IGMATRIX44FMETAFIELD_H

/* igMatrix44fMetaField: the metafield class's metaobject and descriptor calls. */
struct igMemoryPoolView;
struct igMetaField;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igMatrix44fMetaField_metaObject;
/* Parses `count` numbers, optionally bracketed, from `text` into `values`, each `size` bytes wide and
 * read as floats when `isFloat` is set; returns the characters consumed, 0 on failure. */
int FUN_0018be80(const char *text, void *values, int count, int size, int isFloat);

#ifdef __cplusplus
}
#endif

#endif
