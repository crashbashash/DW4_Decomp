#ifndef DW4_IGVIEWMODE_H
#define DW4_IGVIEWMODE_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
extern int g_igViewMode_vtable[4];

extern struct igMetaObject *g_igViewMode_metaObject;
struct CallbackArray *igViewMode_Register(void);
struct igMetaObject *igViewMode_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
