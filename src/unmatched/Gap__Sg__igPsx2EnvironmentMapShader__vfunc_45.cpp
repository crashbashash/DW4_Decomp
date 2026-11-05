#include "dw4/reflected.h"
extern "C" {
int Matrix44_Copy(void *, int);
extern float DAT_004e48a0[4];
extern float DAT_004e48a4[4];
extern float DAT_004e48a8[4];
extern float DAT_004e48ac[4];
extern char GPR_00554bb0;
void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_45(igPsx2EnvironmentMapShader *arg0, int arg1);
}
class DW4VC_128_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_45(igPsx2EnvironmentMapShader *arg0, int arg1) {
    int sp20[12];
    float sp50[4];
    void **temp_a0;

    if (GPR_00554bb0 == 0) {
        DAT_004e48a0[0] = 0;
        DAT_004e48ac[0] = 1.0f;
        DAT_004e48a4[0] = 0;
        GPR_00554bb0 = 1;
        DAT_004e48a8[0] = 0;
    }
    Matrix44_Copy(sp20, arg1 + 0xA4);
    *(float *)((char *)sp50 + 0) = (float)(DAT_004e48a0[0]);
    *(float *)((char *)sp50 + 4) = (float)(DAT_004e48a4[0]);
    *(float *)((char *)sp50 + 8) = (float)(DAT_004e48a8[0]);
    *(float *)((char *)sp50 + 12) = (float)(DAT_004e48ac[0]);
    temp_a0 = (void **)(arg0->_envMapTexGenMatrix);
    ((DW4VC_128_1 *)(temp_a0))->vX((int)(sp20));
}
