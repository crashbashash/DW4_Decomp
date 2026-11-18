#ifndef DW4_IGDATAPUMPINFO_H
#define DW4_IGDATAPUMPINFO_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igDataPumpInfo_metaObject;

void igDataPumpInfo_EnsureRegistered(void);
struct igMetaObject *igDataPumpInfo_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
