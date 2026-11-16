#ifndef DW4_IGCAMERAMODE_H
#define DW4_IGCAMERAMODE_H

struct igMetaObject;
struct igCameraMode;
struct igObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igCameraMode_metaObject;
struct igCameraMode *igCameraMode_Create(int allocator);
void igCameraMode_SetCameraPath(struct igCameraMode *mode, struct igObject *path);

#ifdef __cplusplus
}
#endif

#endif
