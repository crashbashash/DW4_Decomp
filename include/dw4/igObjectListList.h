#ifndef DW4_IGOBJECTLISTLIST_H
#define DW4_IGOBJECTLISTLIST_H

/* igObjectListList: the list class's registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igObjectListList_GetOrCreateMetaObject(void);
void igObjectListList_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
