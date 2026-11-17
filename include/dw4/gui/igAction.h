#ifndef DW4_IGACTION_H
#define DW4_IGACTION_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igAction_metaObject;
struct CallbackArray *igAction_Register(void);
struct igMetaObject *igAction_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
