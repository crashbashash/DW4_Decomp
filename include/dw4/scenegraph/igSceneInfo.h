#ifndef DW4_IGSCENEINFO_H
#define DW4_IGSCENEINFO_H

struct CallbackArray;
struct igMetaObject;
struct igNode;
struct igSceneInfo;

#ifdef __cplusplus
extern "C" {
#endif

void *igSceneInfo_Destroy(struct igSceneInfo *self, short flags);
/* Replaces the held scene graph, retaining the new one and releasing the old. */

#ifdef __cplusplus
}
#endif

#endif
