#ifndef DW4_BOXCAMERA_H
#define DW4_BOXCAMERA_H
/* beCameraCtrl 378ed0: list zero is the mutable rig; regions start at one. */
typedef struct {
    float eye[16], interest[16], start_eye[16], start_interest[16];
    float position[3], frame;
    unsigned current, previous;
    int initialized, timer;
} dw4_boxcamera;
void dw4_boxcamera_tick(dw4_boxcamera *, unsigned region,
    const float eye[16], const float interest[16], const float position[3], float delta);
void dw4_boxcamera_world(const dw4_boxcamera *, float world[16]);
#endif
