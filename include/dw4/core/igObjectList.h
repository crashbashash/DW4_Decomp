#ifndef DW4_IGOBJECTLIST_H
#define DW4_IGOBJECTLIST_H

/* igObjectList, the reference-counted object list, and its class registration. */
struct igMetaObject;
struct CallbackArray;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igObjectList_metaObject;

struct CallbackArray *igObjectList_Register(void);
struct igMetaObject *igObjectList_GetPublishedMetaObject(void);
void igObjectList_EnsureRegistered(void);
int igObjectList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
