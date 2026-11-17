#ifndef DW4_IGSTRINGOBJLIST_H
#define DW4_IGSTRINGOBJLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igStringObjList_metaObject;
void igStringObjList_EnsureRegistered(void);
struct igMetaObject *igStringObjList_GetOrCreateMetaObject(void);
#ifdef __cplusplus
}
#endif

#endif
