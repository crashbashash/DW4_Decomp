#ifndef DW4_IGSTRINGREFLISTLIST_H
#define DW4_IGSTRINGREFLISTLIST_H

/* igStringRefListList: the list class's registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igStringRefListList_GetOrCreateMetaObject(void);
void igStringRefListList_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
