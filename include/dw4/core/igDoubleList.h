#ifndef DW4_IGDOUBLELIST_H
#define DW4_IGDOUBLELIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
void igDoubleList_EnsureRegistered(void);
struct igMetaObject *igDoubleList_GetOrCreateMetaObject(void);
extern struct igMetaObject *g_igDoubleList_metaObject;
#ifdef __cplusplus
}
#endif

#endif
