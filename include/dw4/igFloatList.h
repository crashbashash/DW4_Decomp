#ifndef DW4_IGFLOATLIST_H
#define DW4_IGFLOATLIST_H

struct igFloatList;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igFloatList_metaObject;
struct igMetaObject *igFloatList_GetOrCreateMetaObject(void);
struct igFloatList *igFloatList_Create(int pool);
#ifdef __cplusplus
}
#endif

#endif
