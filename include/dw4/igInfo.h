#ifndef DW4_IGINFO_H
#define DW4_IGINFO_H

/* igInfo: class registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern int g_igInfo_vtable[4];
extern struct igMetaObject *g_igInfo_metaObject;

struct igMetaObject *igInfo_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
