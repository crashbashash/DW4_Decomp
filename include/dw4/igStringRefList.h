#ifndef DW4_IGSTRINGREFLIST_H
#define DW4_IGSTRINGREFLIST_H

/* igStringRefList: the list class's registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igStringRefList_GetOrCreateMetaObject(void);
void igStringRefList_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
