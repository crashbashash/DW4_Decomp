#ifndef DW4_IGNONREFCOUNTEDOBJECTLIST_H
#define DW4_IGNONREFCOUNTEDOBJECTLIST_H

/* igNonRefCountedObjectList: the list class's registration. */
struct CallbackArray;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern struct igMetaObject *g_igNonRefCountedObjectList_metaObject;

struct igMetaObject *igNonRefCountedObjectList_GetPublishedMetaObject(void);
struct CallbackArray *igNonRefCountedObjectList_Register(void);

#ifdef __cplusplus
}
#endif

#endif
