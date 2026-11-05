extern "C" {
int igMatrix44f_SetIdentity(void *);
int Matrix44_SetTranslation(void *, float *);
void FUN_00456b80(int *arg0, float *arg1);
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vX(void *); };
struct P { char pad[12]; float x; float y; };
void FUN_00456b80(int *arg0, float *arg1) {
    float m[16];
    struct P *p;
    float fx;
    float fy;
    float z;

    p = (struct P *)arg0[6];
    if (p != 0) {
        fx = p->x;
        fy = p->y;
        z = 0.0f;
        igMatrix44f_SetIdentity(m);
        arg1[0] = arg1[0] - fx;
        arg1[1] = arg1[1] - fy;
        arg1[2] = arg1[2] - z;
        Matrix44_SetTranslation(m, arg1);
        ((Obj *)arg0[7])->vX(m);
    }
}
