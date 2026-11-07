extern "C" {
int FUN_00191860(void *, float, float, float, float, float, float);
int FUN_001919d0(void *, float, float, float, float, float);
int FUN_00191b10(void *, void *, void *, void *);
int FUN_001d5f70(void *, int, void *, void *, void *);
}
struct Mx { float m[16]; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(Mx *); };
struct O { char p0[32]; float f32, f36, f40, f44, f48, f52, f56; char p60[28]; V *f88; V *f92; char p96[28]; float f124, f128; char p132[12]; V *f144; char p148[60]; unsigned char f208; char p209[3]; float f212, f216, f220, f224; };
extern "C" void FUN_001d6060(O *arg0, int arg1);
void FUN_001d6060(O *arg0, int arg1) {
    float spF0[3];
    Mx spB0;
    Mx sp70;
    Mx sp30;
    float t;

    spF0[0] = arg0->f32 + arg0->f44;
    spF0[1] = arg0->f36 + arg0->f48;
    spF0[2] = arg0->f40 + arg0->f52;
    FUN_00191b10(&spB0, &arg0->f32, spF0, (char *)arg0 + 132);
    if (arg0->f208 != 0) {
        FUN_00191860(&sp70, arg0->f224, arg0->f220, arg0->f216, arg0->f212, arg0->f124, arg0->f128);
    } else {
        t = 0.0174532924f * (2.0f * arg0->f56);
        FUN_001919d0(&sp70, t, t, 1.0f, arg0->f124, arg0->f128);
    }
    arg0->f88->vX(&spB0);
    arg0->f92->vX(&sp70);
    FUN_001d5f70(arg0, arg1, &spB0, &sp70, &sp30);
    arg0->f144->vX(&sp30);
}
