#include "dw4/reflected.h"
extern "C" {
void FUN_004578c0(igViewModel *, int *);
extern int DAT_0058cd48[4];
extern int DAT_0058cd50[4];
extern int DAT_0058cd58[4];
void Gap__Bec__beCameraMode__vfunc_29(beCameraMode *self);
}
class CameraVt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int update(); };

void Gap__Bec__beCameraMode__vfunc_29(beCameraMode *self) {
    int hfovChanged[4];
    int farChanged[4];
    int nearChanged[4];
    float farPlane;
    float nearPlane;
    igCamera *camera;
    igViewModel *model;

    if (self->_camera != 0) {
        ((CameraVt *)self->_camera)->update();
        model = (igViewModel *)self->_model;
        camera = (igCamera *)self->_camera;
        farPlane = camera->_farPlane;
        nearPlane = camera->_nearPlane;
        model->_hfov = camera->_horizontalFieldOfView;
        hfovChanged[0] = 2;
        hfovChanged[1] = 0;
        hfovChanged[2] = DAT_0058cd48[0];
        FUN_004578c0(model, hfovChanged);
        model->_farPlane = farPlane;
        farChanged[0] = 2;
        farChanged[1] = 0;
        farChanged[2] = DAT_0058cd58[0];
        FUN_004578c0(model, farChanged);
        nearPlane = (nearPlane == 0.0f) ? farPlane / 1000.0f : nearPlane;
        model->_nearPlane = nearPlane;
        nearChanged[0] = 2;
        nearChanged[1] = 0;
        nearChanged[2] = DAT_0058cd50[0];
        FUN_004578c0(model, nearChanged);
    }
}
