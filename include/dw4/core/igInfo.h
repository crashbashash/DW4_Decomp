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

struct igMetaObject *igInfo_GetPublishedMetaObject(void);
struct igInfo *igInfo_Destroy(struct igInfo *self, short deleteFlag);

#ifdef __cplusplus
}
#endif

#endif
