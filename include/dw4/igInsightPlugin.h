#ifndef DW4_IGINSIGHTPLUGIN_H
#define DW4_IGINSIGHTPLUGIN_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igInsightPlugin_metaObject;
struct CallbackArray *igInsightPlugin_Register(void);
struct igMetaObject *igInsightPlugin_GetPublishedMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
