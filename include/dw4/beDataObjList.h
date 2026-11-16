#ifndef DW4_BEDATAOBJLIST_H
#define DW4_BEDATAOBJLIST_H

struct beDataObjList;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beDataObjList *beDataObjList_Create(int allocator);
void beDataObjList_EnsureRegistered(void);
struct igMetaObject *beDataObjList_GetOrCreateMetaObject(void);

extern struct igMetaObject *g_beDataObjList_metaObject;

#ifdef __cplusplus
}
#endif

#endif
