class T { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX();
  char pad[20]; float f24; float f28; float f32; float f36; };
struct M { int p0; int p1; T *t; };
struct O { char pad[24]; M *m; char pad2[4]; char f32; };
extern "C" {
extern float DAT_004e1170[4];
extern float DAT_004e1174[4];
extern float DAT_004e1178[4];
extern float DAT_004e117c[4];
}
extern "C" void FUN_004569c0(O *arg0, int arg1) {
    T *temp_a0;
    arg0->f32 = arg1;
    if (arg1 != 0) {
        temp_a0 = arg0->m->t;
        temp_a0->f24 = 1.0f;
        temp_a0->f28 = 1.0f;
        temp_a0->f32 = 1.0f;
        temp_a0->f36 = 1.0f;
        temp_a0->vX();
        return;
    }
    temp_a0 = arg0->m->t;
    temp_a0->f24 = DAT_004e1170[0];
    temp_a0->f28 = DAT_004e1174[0];
    temp_a0->f32 = DAT_004e1178[0];
    temp_a0->f36 = DAT_004e117c[0];
    temp_a0->vX();
}
