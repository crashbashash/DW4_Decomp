#ifndef DW4_BEDATAOBJLISTLIST_H
#define DW4_BEDATAOBJLISTLIST_H

struct beDataObjListList;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beDataObjListList *beDataObjListList_Create(int allocator);
void beDataObjListList_EnsureRegistered(void);
struct igMetaObject *beDataObjListList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
