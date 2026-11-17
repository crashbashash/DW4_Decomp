#ifndef DW4_IGSCENEINFO_H
#define DW4_IGSCENEINFO_H

struct CallbackArray;
struct igMetaObject;
struct igSceneInfo;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igSceneInfo_metaObject;
void igSceneInfo_CollectCameras(struct igSceneInfo *info);
void igSceneInfo_ComputeAnimationRange(struct igSceneInfo *info);
struct igSceneInfo *igSceneInfo_CreateInstance(int allocator);
void *igSceneInfo_Destroy(struct igSceneInfo *self, short flags);
struct igMetaObject *igSceneInfo_GetMetaObject(void);
struct igMetaObject *igSceneInfo_GetOrCreateMetaObject(void);
struct CallbackArray *igSceneInfo_Register(void);

#ifdef __cplusplus
}
#endif

#endif
