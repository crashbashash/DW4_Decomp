struct Obj { int w0; int references; };
struct T {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual int vX();
};
extern "C" {
int FUN_001c5e20(T *);
int igMetaObject_CountInstances(int, int);
int igObject_Destroy(void *);
extern Obj *DAT_00562798[4];
extern Obj *DAT_005627a0[4];
extern Obj *DAT_005627a8[4];
extern Obj *DAT_005627b0[4];
extern Obj *DAT_005627b8[4];
extern Obj *DAT_005627c0[4];
extern Obj *DAT_005627c8[4];
extern Obj *DAT_005627d0[4];
extern Obj *DAT_005627d8[4];
void Gap__Sg__igPlanarShadowShader__vfunc_10(T *arg0)
{
    Obj *o;
    if (igMetaObject_CountInstances(arg0->vX(), 1) == 0) {
        o = DAT_00562798[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = DAT_005627a0[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = DAT_005627a8[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = DAT_005627b0[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = DAT_005627b8[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = DAT_005627c8[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = DAT_005627c0[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = DAT_005627d0[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = DAT_005627d8[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    FUN_001c5e20(arg0);
}
}
