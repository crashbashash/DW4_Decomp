#ifndef DW4_IGATTRLIST_H
#define DW4_IGATTRLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igAttrList_metaObject;
struct igMetaObject *igAttrList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
