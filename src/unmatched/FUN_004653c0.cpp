#include "dw4/reflected.h"
extern "C" {
int FUN_004578c0(...);
extern int DAT_0058cd48[4];
extern int DAT_0058cd50[4];
extern int DAT_0058cd58[4];
void FUN_004653c0(igCameraMode *arg0);
}
class DW4VC_140_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(); };
void FUN_004653c0(igCameraMode *arg0) {
    int spA[4];
    int spB[4];
    int spC[4];
    float temp_f21;
    float var_f20;
    igCamera *temp_v1;
    igViewModel *temp_s0;

    if (arg0->_camera != 0) {
        ((DW4VC_140_0 *)arg0->_camera)->vX();
        temp_s0 = (igViewModel *)arg0->_model;
        temp_v1 = (igCamera *)arg0->_camera;
        temp_f21 = temp_v1->_farPlane;
        var_f20 = temp_v1->_nearPlane;
        temp_s0->_hfov = (float) temp_v1->_horizontalFieldOfView;
        spA[0] = 2;
        spA[1] = 0;
        spA[2] = DAT_0058cd48[0];
        FUN_004578c0(temp_s0, spA);
        temp_s0->_farPlane = temp_f21;
        spB[0] = 2;
        spB[1] = 0;
        spB[2] = DAT_0058cd58[0];
        FUN_004578c0(temp_s0, spB);
        var_f20 = (var_f20 == 0.0f) ? temp_f21 / 1000.0f : var_f20;
        temp_s0->_nearPlane = var_f20;
        spC[0] = 2;
        spC[1] = 0;
        spC[2] = DAT_0058cd50[0];
        FUN_004578c0(temp_s0, spC);
    }
}
