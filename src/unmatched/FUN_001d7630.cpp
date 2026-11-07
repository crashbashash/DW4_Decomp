extern "C" {
void igMatrix44f_SetIdentity(float *);
void FUN_001904f0(float *, float *, float *);
void FUN_00190c60(float *, float *);
void FUN_00190a10(float *, float *);
void FUN_001908f0(float *, float *);
void FUN_00191860(float *, float, float, float, float, float, float);
void FUN_001919d0(float *, float, float, float, float, float);
void FUN_00191b10(float *, float *, float *, float *);
extern float DAT_004e0f30[16];
void FUN_001d7630(void *arg0, float *arg1);
}
struct G { int pad[2]; int f8; };
extern "C" { extern G *DAT_0055ece0[4]; extern G *DAT_0055ee30[4]; }
class Ob { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();  virtual void vX(float *); };
struct Src { char p0[96]; float f96; char p1[16]; float f116, f120, f124, f128, f132, f136; };
struct T {
    char p0[36]; float p[3]; float q[3]; float f60; float f64; float f68; float f72[5];
    Ob *f92; Ob *f96; int f100; float f104; float f108; char p2[80]; Src *f192; int f196; int f200; char f204[4]; unsigned char f208; char p3[3];
    float f212, f216, f220, f224;
};
void FUN_001d7630(void *arg0, float *arg1) {
    T *t = (T *)arg0;
    float m1[16];
    float m2[16];
    float m3[16];
    float m4[16];
    float v1[3];
    float v2[3];
    float v3[3];
    float *s2, *s0, *s4;
    float f20;
    Src *a = t->f192;
    if (a != 0) {
        t->p[0] = a->f116;
        t->p[1] = a->f120;
        t->p[2] = a->f124;
        Src *b = t->f192;
        t->q[0] = b->f128;
        t->q[1] = b->f132;
        t->q[2] = b->f136;
        t->f60 = t->f192->f96;
    }
    v1[0] = t->p[0] + t->q[0];
    v1[1] = t->p[1] + t->q[1];
    v1[2] = t->p[2] + t->q[2];
    FUN_00191b10(m1, t->p, v1, t->f72);
    if (t->f208 != 0) {
        FUN_00191860(m2, t->f224, t->f220, t->f216, t->f212, t->f64, t->f68);
    } else {
        float f12 = 0.0174532924f * (2.0f * t->f60);
        FUN_001919d0(m2, f12, f12, 1.0f, t->f64, t->f68);
    }
    t->f92->vX(m1);
    t->f96->vX(m2);
    s2 = (float *)(t->f100 + DAT_0055ece0[0]->f8);
    FUN_001908f0(s2, arg1);
    FUN_001904f0(s2, s2, m1);
    FUN_001904f0(s2, s2, m2);
    igMatrix44f_SetIdentity(m3);
    v2[0] = 0.5f; v2[2] = 0.0f; v2[1] = -0.5f;
    FUN_00190c60(m3, v2);
    v3[0] = 0.5f; v3[1] = 0.5f; v3[2] = 0.0f;
    FUN_00190a10(m3, v3);
    FUN_001904f0(s2, s2, m3);
    s0 = (float *)(t->f196 + DAT_0055ee30[0]->f8);
    s4 = (float *)(t->f200 + DAT_0055ee30[0]->f8);
    FUN_001908f0(s4, arg1);
    FUN_001904f0(s4, s4, m1);
    f20 = t->f68 - t->f64;
    FUN_001908f0(m4, DAT_004e0f30);
    m4[11] = 128.0f / f20;
    m4[15] = 128.0f + (128.0f * (t->f108 + t->f64)) / f20;
    FUN_001904f0(s4, s4, m4);
    m4[11] = -128.0f / f20;
    m4[15] = (128.0f * -t->f64) / f20;
    FUN_001908f0(s0, m4);
}
