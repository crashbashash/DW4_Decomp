#include "dw4/reflected.h"

extern "C" int Gap__Bec__beCameraMode__vfunc_20(void);
extern "C" void Gap__Bec__beCameraMode__vfunc_23(void);
extern "C" void Gap__Bec__beCameraMode__vfunc_24(void);
extern "C" void Gap__Bec__beCameraMode__vfunc_25(void);
extern "C" void Gap__Bec__beCameraMode__vfunc_26(void);
extern "C" void Gap__Bec__beCameraMode__vfunc_27(void);
class DW4VC_144_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int vX(); };
extern "C" void Gap__Bec__beCameraMode__vfunc_30(beCameraMode *arg0);
extern "C" void igModel_NotifyViews(igViewModel *, int *);
extern "C" int DAT_0058cd48[4];
extern "C" int DAT_0058cd50[4];
extern "C" int DAT_0058cd58[4];
class CameraVt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int update(); };
extern "C" void Gap__Bec__beCameraMode__vfunc_29(beCameraMode *self);
typedef struct CameraMatrix { float m[16]; } CameraMatrix;
typedef struct CameraVector4 { float v[4]; } CameraVector4;
extern "C" void igMatrix44f_SetIdentity(CameraMatrix *);
extern "C" void FUN_00190ed0(CameraMatrix *, float, float, float);
extern "C" void FUN_00191230(CameraMatrix *, float *, float *, float *);
extern "C" void FUN_00191e30(void *, void *, CameraMatrix *);
extern "C" void FUN_001c5b30(int, CameraMatrix *, long long);
extern "C" void Matrix44_GetTranslation(CameraMatrix *, CameraVector4 *);
extern "C" void Matrix44_SetTranslation(CameraMatrix *, CameraVector4 *);
extern "C" int DAT_0058cd38[4];
extern "C" void Gap__Bec__beCameraMode__vfunc_28(beCameraMode *self);
extern "C" int g_beCameraMode_metaObject[4];

void Gap__Bec__beCameraMode__vfunc_30(beCameraMode *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(arg0->_camera);
    if (temp_a0 != 0) {
        ((DW4VC_144_0 *)(temp_a0))->vX();
    }
}

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
        igModel_NotifyViews(model, hfovChanged);
        model->_farPlane = farPlane;
        farChanged[0] = 2;
        farChanged[1] = 0;
        farChanged[2] = DAT_0058cd58[0];
        igModel_NotifyViews(model, farChanged);
        nearPlane = (nearPlane == 0.0f) ? farPlane / 1000.0f : nearPlane;
        model->_nearPlane = nearPlane;
        nearChanged[0] = 2;
        nearChanged[1] = 0;
        nearChanged[2] = DAT_0058cd50[0];
        igModel_NotifyViews(model, nearChanged);
    }
}

void Gap__Bec__beCameraMode__vfunc_28(beCameraMode *self) {
    float a, b, c;
    int composed;
    CameraVector4 translation;
    CameraMatrix matrix;
    int changed[4];
    igViewModel *model;
    if (self->_camera != 0) {
        if (self->_isFreeze) {
            self->_svWorldTimeL = ((igInsightCore *)self->_insight)->_worldTime;
            return;
        }
        if (!self->_isEnd) {
            long long now = ((igInsightCore *)self->_insight)->_worldTime;
            /* matching construct: hand sweep (about 25 spellings) — an unsigned delta with a signed clamp sets the daddu operand order */
            unsigned long long delta = self->_svWorldTimeL != 0 ? now - self->_svWorldTimeL : 0;
            if ((long long)delta > 50000000) delta = 50000000;
            self->_nowTimeL = delta + self->_nowTimeL;
            self->_svWorldTimeL = now;
            if (self->_nowTimeL >= self->_timeLength) {
                self->_isEnd = 1;
                self->_nowTimeL = self->_timeLength;
            }
        }
        igMatrix44f_SetIdentity(&matrix);
        model = (igViewModel *)self->_model;
        FUN_001c5b30(self->_cameraPath, &matrix, self->_nowTimeL);
        a = 0; b = 0; c = 0;
        FUN_00191230(&matrix, &a, &b, &c);
        Matrix44_GetTranslation(&matrix, &translation);
        FUN_00190ed0(&matrix, a, b, c);
        Matrix44_SetTranslation(&matrix, &translation);
        FUN_00191e30(&composed, model->_viewMatrix, &matrix);
        changed[0] = 2;
        changed[1] = 0;
        changed[2] = DAT_0058cd38[0];
        igModel_NotifyViews(model, changed);
    }
}

int Gap__Bec__beCameraMode__vfunc_20(void)
{
    return g_beCameraMode_metaObject[0];
}

/* Slot 23: empty body. */
void Gap__Bec__beCameraMode__vfunc_23(void)
{
}

/* Slot 24: empty body. */
void Gap__Bec__beCameraMode__vfunc_24(void)
{
}

/* Slot 25: empty body. */
void Gap__Bec__beCameraMode__vfunc_25(void)
{
}

/* Slot 26: empty body. */
void Gap__Bec__beCameraMode__vfunc_26(void)
{
}

/* Slot 27: empty body. */
void Gap__Bec__beCameraMode__vfunc_27(void)
{
}

