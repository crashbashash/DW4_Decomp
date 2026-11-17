#ifndef DW4_BECAMERAMODE_H
#define DW4_BECAMERAMODE_H

struct beCameraMode;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beCameraMode *beCameraMode_Create(int allocator);

extern struct igMetaObject *g_beCameraMode_metaObject;

#ifdef __cplusplus
}
#endif

#endif
