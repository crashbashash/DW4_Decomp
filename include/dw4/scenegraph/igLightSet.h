#ifndef DW4_IGLIGHTSET_H
#define DW4_IGLIGHTSET_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igLightSet_metaObject;

struct igMetaObject *igLightSet_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
