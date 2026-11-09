#include "dw4/reflected.h"
struct V4 { float a, b, c, d; };
struct Frame { void *f0; char pad4[96]; float eye[8]; float center[10]; float range; char pad176[56]; int f232; void *f236; };
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(V4 *); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(int); virtual void v132(float); };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(void *); virtual void v132(void *); virtual void v136(void *); virtual void d33(); virtual void v144(void *); char pad[8]; int f12; char pad2[128]; char b144; };
struct N { char pad[28]; int f28; };
struct Q { char pad[16]; igObject *f16; };
struct Z { char pad[8]; char b8; char pad1[3]; int f12; char pad2[8]; char b24; };
struct Y { char pad[24]; char b24; };
struct P { char pad[16]; int f16; int f20; int f24; int f28; int f32; C *f36; Q *f40; int f44; int f48; int f52; N *f56; char pad3[12]; Z *f72; int pad4; igObject *f80; };
extern "C" {
int FUN_00100610(...);
void *FUN_001007e0(...);
void *FUN_00138ee0(...);
void *FUN_0013b490(...);
void *FUN_0019fde0(...);
int FUN_001c5160(void *, float);
int FUN_001c5d10(...);
void *FUN_00238110(...);
int FUN_00460e00(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int igObject_Destroy(...);
extern float DAT_004e1098[4];
extern float DAT_004e109c[4];
extern float DAT_004e10a0[4];
extern int DAT_004e1170[4];
extern Frame *DAT_0056dc50[4];
int FUN_0045f200(...);
void Gap__Viewer__igViewerRenderer__vfunc_13(P *arg0);
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(void *object) : p((T *)object) {}
    ~igSmartPointer() {
        T *object = p;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
};
struct Tag { };
static inline void *createFirst() {
    Tag tag = Tag();
    return FUN_00138ee0(0);
}
static inline void *createSecond() {
    Tag tag = Tag();
    return FUN_0013b490(0);
}
static inline void *createThird() {
    Tag tag = Tag();
    return FUN_0019fde0(0, 1);
}
void Gap__Viewer__igViewerRenderer__vfunc_13(P *arg0) {
    V4 sp40;
    float sp58[3];
    Frame *s0;
    igObject *t;
    igSmartPointer<igObject> first(createFirst());
    sp40.a = 1.0f; sp40.b = 1.0f; sp40.c = 1.0f; sp40.d = 1.0f;
    ((A *)first.p)->vX(&sp40);
    if (DAT_0056dc50[0] == 0) {
        Frame *f = (Frame *)FUN_001007e0(240);
        if (f != 0) f = (Frame *)FUN_00238110(f);
        DAT_0056dc50[0] = f;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    s0 = DAT_0056dc50[0];
    igSmartPointer<igObject> second(createSecond());
    ((B *)second.p)->v128(4);
    ((B *)second.p)->v132(s0->range);
    arg0->f36->v128(s0->eye);
    arg0->f36->v136(&DAT_004e1170[0]);
    arg0->f36->v132(s0->center);
    sp58[0] = -DAT_004e1098[0];
    sp58[1] = -DAT_004e109c[0];
    sp58[2] = -DAT_004e10a0[0];
    arg0->f36->v144(sp58);
    {
        C *c = arg0->f36;
        c->f12 = 0;
        c->b144 = 1;
    }
    {
        igObject *s1 = (igObject *)arg0->f36;
        Q *s0b = arg0->f40;
        if (s1 != 0) {
            s1->_refCount = s1->_refCount + 1;
        }
        t = s0b->f16;
        if (t) {
            t->_refCount = t->_refCount - 1;
            if ((t->_refCount & 0x7FFFFF) == 0) igObject_Destroy(t);
        }
        s0b->f16 = s1;
    }
    if (DAT_0056dc50[0] != 0) {
        if (--DAT_0056dc50[0]->f232 <= 0) {
            Frame *s0c = DAT_0056dc50[0];
            if (s0c != 0) {
                if (&s0c->f236) {
                    void *p = s0c->f236;
                    if (p != 0) {
                        int *h = (int *)((char *)(p) - 8);
                        int rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (s0c != 0) {
                    void *p = s0c->f0;
                    if (p != 0) {
                        int *h = (int *)((char *)(p) - 8);
                        int rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                FUN_00100610(s0c);
            }
            DAT_0056dc50[0] = 0;
        }
    }
    FUN_00460e00(arg0, first.p);
    FUN_00460e00(arg0, second.p);
    FUN_00460e00(arg0, arg0->f16);
    FUN_00460e00(arg0, arg0->f20);
    FUN_00460e00(arg0, arg0->f24);
    FUN_00460e00(arg0, arg0->f28);
    FUN_00460e00(arg0, arg0->f32);
    FUN_001c5d10(arg0->f44, arg0->f52);
    FUN_001c5d10(arg0->f52, arg0->f56);
    ObjectList_AppendRetained(arg0->f56->f28, arg0->f36);
    FUN_001c5d10(arg0->f44, arg0->f48);
    arg0->f72->b8 = 1;
    arg0->f72->f12 = (int)&FUN_0045f200;
    arg0->f72->b24 = 1;
    igSmartPointer<igObject> third(createThird());
    ((Y *)third.p)->b24 = 1;
    FUN_001c5160(third.p, 1.1f);
    t = third.p;
    if (t) t->_refCount = t->_refCount + 1;
    {
        igObject *o = arg0->f80;
        if (o) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    arg0->f80 = t;
}
