#include "dw4/reflected.h"
#include "dw4/igCameraDispatchView.h"
#include "dw4/beCameraMode.h"
#include "dw4/igGraphPath.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igModel.h"
#include "dw4/igViewModel.h"

extern "C" igMetaObject *beCameraMode_GetMeta(void);
extern "C" void igViewMode_OnKeyEvent(void);
extern "C" void igViewMode_OnMouseMove(void);
extern "C" void igViewMode_OnMouseButton(void);
extern "C" void igViewMode_OnStickEvent(void);
extern "C" void igViewMode_OnButtonEvent(void);
extern "C" void beCameraMode_OnDetach(beCameraMode *self);
extern "C" void beCameraMode_OnAttach(beCameraMode *self);
typedef struct CameraMatrix { float m[16]; } CameraMatrix;
typedef struct CameraVector4 { float v[4]; } CameraVector4;
extern "C" void igMatrix44f_GetEulerAngles(CameraMatrix *, float *, float *, float *);
extern "C" void igMatrix44f_InvertOrthonormal(void *, void *, CameraMatrix *);
extern "C" void beCameraMode_Update(beCameraMode *self);

void beCameraMode_OnDetach(beCameraMode *self) {
    igCameraDispatchView *camera;

    camera = (igCameraDispatchView *)(self->_camera);
    if (camera != 0) {
        camera->Deactivate();
    }
}

void beCameraMode_OnAttach(beCameraMode *self) {
    int hfovChanged[4];
    int farChanged[4];
    int nearChanged[4];
    float farPlane;
    float nearPlane;
    igCamera *camera;
    igViewModel *model;

    if (self->_camera != 0) {
        ((igCameraDispatchView *)self->_camera)->Activate();
        model = (igViewModel *)self->_model;
        camera = (igCamera *)self->_camera;
        farPlane = camera->_farPlane;
        nearPlane = camera->_nearPlane;
        model->_hfov = camera->_horizontalFieldOfView;
        hfovChanged[0] = 2;
        hfovChanged[1] = 0;
        hfovChanged[2] = (int)g_igViewModel_hfovMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)hfovChanged);
        model->_farPlane = farPlane;
        farChanged[0] = 2;
        farChanged[1] = 0;
        farChanged[2] = (int)g_igViewModel_farPlaneMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)farChanged);
        nearPlane = (nearPlane == 0.0f) ? farPlane / 1000.0f : nearPlane;
        model->_nearPlane = nearPlane;
        nearChanged[0] = 2;
        nearChanged[1] = 0;
        nearChanged[2] = (int)g_igViewModel_nearPlaneMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)nearChanged);
    }
}

void beCameraMode_Update(beCameraMode *self) {
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
        igMatrix44f_SetIdentity((float *)&matrix);
        model = (igViewModel *)self->_model;
        igGraphPath_GetTransform((igGraphPath *)self->_cameraPath, (igMatrix44f *)&matrix, self->_nowTimeL);
        a = 0; b = 0; c = 0;
        igMatrix44f_GetEulerAngles(&matrix, &a, &b, &c);
        igMatrix44f_GetTranslation((const float *)&matrix, (float *)&translation);
        igMatrix44f_MakeEulerRotation(&matrix, a, b, c);
        igMatrix44f_SetTranslation((float *)&matrix, (const float *)&translation);
        igMatrix44f_InvertOrthonormal(&composed, model->_viewMatrix, &matrix);
        changed[0] = 2;
        changed[1] = 0;
        changed[2] = (int)g_igViewModel_viewMatrixMetaField;
        igModel_NotifyViews((igModel *)model, (ModelChange *)changed);
    }
}

igMetaObject *beCameraMode_GetMeta(void)
{
    return g_beCameraMode_metaObject;
}

/* Slot 23: empty body. */
void igViewMode_OnKeyEvent(void)
{
}

/* Slot 24: empty body. */
void igViewMode_OnMouseMove(void)
{
}

/* Slot 25: empty body. */
void igViewMode_OnMouseButton(void)
{
}

/* Slot 26: empty body. */
void igViewMode_OnStickEvent(void)
{
}

/* Slot 27: empty body. */
void igViewMode_OnButtonEvent(void)
{
}

