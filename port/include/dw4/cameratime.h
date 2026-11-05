/* beCameraMode vfunc_28 time state; projection/path traversal stays with scene. */
#ifndef DW4_CAMERATIME_H
#define DW4_CAMERATIME_H
#include <stdint.h>
typedef struct {
    uint64_t last, time, end;
    int loaded, finished, frozen;
} dw4_camera_time;
void dw4_camera_time_tick(dw4_camera_time *, uint64_t world_ns);
#endif
