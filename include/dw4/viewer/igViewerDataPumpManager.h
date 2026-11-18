#ifndef DW4_IGVIEWERDATAPUMPMANAGER_H
#define DW4_IGVIEWERDATAPUMPMANAGER_H

struct igMetaObject;

struct igObject;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif
struct igObject *igViewerDataPumpManager_Create(struct igMemoryPoolView *pool);

extern struct igMetaObject *g_igViewerDataPumpManager_metaObject;

#ifdef __cplusplus
}
#endif

#endif
