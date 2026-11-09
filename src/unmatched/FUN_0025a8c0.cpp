#include "dw4/reflected.h"
struct Frame {
    void *f0;
    char pad[228];
    int f232;
    void *f236;
};
struct Ev { int a; int b; int c; int d; };
struct Tm {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int vA(); virtual void d25(); virtual void vB(); virtual void d27(); virtual void d28(); virtual void vC();
    int rc;
};
struct App { int f0; igViewerSceneInfoManager *f4; char pad[16]; int f24; };
extern "C" {
int FUN_00100610(...);
Frame *FUN_001007e0(...);
float __floatdisf(int);
int fptodp(float);
Frame *FUN_00238110(...);
int FUN_00239390(...);
int FUN_00259f80(...);
Tm *FUN_002b79d0(...);
int FUN_003082b0(...);
int FUN_004578c0(...);
int FUN_00463b30(...);
int FUN_00463b70(...);
int FUN_00463bb0(...);
int FUN_00463bc0(...);
int FUN_00463c70(...);
int StringChunk_ReleaseHeader(...);
int igObject_Destroy(...);
int thunk_FUN_00238ed0(...);
extern int DAT_004ecf70[4];
extern Frame *DAT_0056dc50[4];
extern int DAT_0058cab8[4];
extern int DAT_0058cac0[4];
extern int DAT_0058cac8[4];
extern int DAT_0058cad0[4];
extern unsigned char GPR_00554bf0;
void FUN_0025a8c0(App *arg0);
}
struct TimerType {};
static inline Tm *createTimer(TimerType) { return FUN_002b79d0(0); }
struct Ref {
    Tm *p;
    Ref(Tm *object) : p(object) {}
    ~Ref() {
        Tm *object = p;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
void FUN_0025a8c0(App *arg0) {
    Ev e0;
    Ev e1;
    Ev e2;
    Ev e3;
    int s2;
    float temp_f12;
    void *p;
    int rc;
    int i;
    int s1;
    int *h;
    igViewerParameters *obj;
    int r;
    Frame *f;
    int s4;
    if (arg0->f24 != 0) {
        FUN_00239390();
        thunk_FUN_00238ed0();
        FUN_00463b30(arg0);
        FUN_00259f80(arg0);
        FUN_00463c70(arg0);
        obj = (igViewerParameters *)arg0->f4->_parameters;
        obj->_showGui = 0;
        e0.a = 2; e0.b = 0; e0.c = DAT_0058cab8[0];
        FUN_004578c0(obj, &e0);
        obj->_showBoundingBox = 0;
        e1.a = 2; e1.b = 0; e1.c = DAT_0058cac0[0];
        FUN_004578c0(obj, &e1);
        obj->_showNormals = 0;
        e2.a = 2; e2.b = 0; e2.c = DAT_0058cac8[0];
        FUN_004578c0(obj, &e2);
        if (DAT_0056dc50[0] == 0) {
            Frame *v = FUN_001007e0(240);
            if (v != 0) v = FUN_00238110(v);
            DAT_0056dc50[0] = v;
        }
        DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
        s2 = *(int *)((char *)DAT_0056dc50[0] + 220);
        if (s2 < 0) s2 = 0;
        s1 = *(int *)((char *)DAT_0056dc50[0] + 224);
        if (s1 < 0) s1 = 0;
        if (DAT_0056dc50[0] != 0) {
            if (--DAT_0056dc50[0]->f232 <= 0) {
                f = DAT_0056dc50[0];
                if (f != 0) {
                    if (&f->f236) {
                        p = f->f236;
                        if (p != 0) {
                            h = (int *)((char *)(p) - 8);
                            rc = *(int *)((char *)(p) - 4) - 1;
                            *(int *)((char *)(p) - 4) = rc;
                            if (rc == 0) StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                    if (f != 0) {
                        p = f->f0;
                        if (p != 0) {
                            h = (int *)((char *)(p) - 8);
                            rc = *(int *)((char *)(p) - 4) - 1;
                            *(int *)((char *)(p) - 4) = rc;
                            if (rc == 0) StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                    FUN_00100610(f);
                }
                DAT_0056dc50[0] = 0;
            }
        }
        FUN_00463bc0(arg0);
        s4 = 0;
        if (0 < s2) {
            do {
                FUN_00463bb0(arg0);
                s4++;
            } while (s4 < s2);
        }
        FUN_00463bc0(arg0);
        Ref sp(createTimer(TimerType()));
        sp.p->vC();
        i = 0;
        if (0 < s1 - 1) {
            do {
                FUN_00463bb0(arg0);
                i++;
            } while (i < s1 - 1);
        }
        obj->_flushFrames = 1;
        e3.a = 2; e3.b = 0; e3.c = DAT_0058cad0[0];
        FUN_004578c0(obj, &e3);
        FUN_00463bb0(arg0);
        sp.p->vB();
        temp_f12 = (1e9f * (float)s1) / __floatdisf(sp.p->vA());
        if (GPR_00554bf0 == 0) {
            r = FUN_003082b0(&DAT_004ecf70[0], s1, fptodp(temp_f12));
            if (r != 1 && r == 2) GPR_00554bf0 = 1;
        }
        FUN_00463b70(arg0);
    }
}
