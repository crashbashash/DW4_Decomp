#include "dw4/reflected.h"
extern "C" {
typedef struct CameraMatrix { float m[16]; } CameraMatrix;
typedef struct CameraVector4 { float v[4]; } CameraVector4;
void igMatrix44f_SetIdentity(CameraMatrix *);
void FUN_00190ed0(CameraMatrix *, float, float, float);
void FUN_00191230(CameraMatrix *, float *, float *, float *);
void FUN_00191e30(void *, void *, CameraMatrix *);
void FUN_001c5b30(int, CameraMatrix *, long long);
void FUN_004578c0(igViewModel *, int *);
void Matrix44_GetTranslation(CameraMatrix *, CameraVector4 *);
void Matrix44_SetTranslation(CameraMatrix *, CameraVector4 *);
extern int DAT_0058cd38[4];
void Gap__Bec__beCameraMode__vfunc_28(beCameraMode *self);
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
        FUN_004578c0(model, changed);
    }
}
