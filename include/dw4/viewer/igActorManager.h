#ifndef DW4_IGACTORMANAGER_H
#define DW4_IGACTORMANAGER_H

struct igMetaObject;

struct igObject;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif
struct igObject *igActorManager_Create(struct igMemoryPoolView *pool);

extern struct igMetaObject *g_igActorManager_metaObject;

#ifdef __cplusplus
}
#endif

#endif
