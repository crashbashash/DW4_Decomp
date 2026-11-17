#ifndef DW4_IGNAMEDOBJECTLIST_H
#define DW4_IGNAMEDOBJECTLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igNamedObjectList_metaObject;
struct igMetaObject *igNamedObjectList_GetOrCreateMetaObject(void);
#ifdef __cplusplus
}
#endif

#endif
