#ifndef DW4_IGNONREFCOUNTEDOBJECTLIST_H
#define DW4_IGNONREFCOUNTEDOBJECTLIST_H

/* igNonRefCountedObjectList: the list class's registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igNonRefCountedObjectList_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
