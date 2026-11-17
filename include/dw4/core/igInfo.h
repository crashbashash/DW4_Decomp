#ifndef DW4_IGINFO_H
#define DW4_IGINFO_H

/* igInfo: class registration. */
struct igInfo;
struct CallbackArray;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern int g_igInfo_vtable[4];
extern struct igMetaObject *g_igInfo_metaObject;

struct igMetaObject *igInfo_GetPublishedMetaObject(void);
struct CallbackArray *igInfo_Register(void);
struct igInfo *igInfo_Destroy(struct igInfo *self, short deleteFlag);

#ifdef __cplusplus
}
#endif

#endif
