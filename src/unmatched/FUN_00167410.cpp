#include "dw4/reflected.h"
extern "C" {
int png_destroy_info_struct(...);
int png_destroy_read_struct(...);
int png_destroy_write_struct(...);
int FUN_00300f50(...);
int igObject_Destroy(...);
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };

struct Owner { char pad[92]; Obj *f92; };
extern "C" int FUN_00167410(Owner *arg0, int arg1, int arg2, int arg3, void *arg4, void *arg5, int arg6, int arg7) {
    int sp5C;
    int sp58;
    int sp54;
    Obj *o;

    sp54 = arg1;
    sp58 = arg2;
    sp5C = arg3;
    if (arg4 != 0) {
        FUN_00300f50(arg0, arg4);
    }
    if (arg5 != 0) {
        FUN_00300f50(arg0, arg5);
    }
    if (sp54 != 0) {
        if (arg7 != 0) {
            png_destroy_read_struct(&sp54, &sp58, &sp5C);
        } else {
            png_destroy_info_struct(sp54, &sp5C);
            png_destroy_write_struct(&sp54, &sp58);
        }
    }
    o = arg0->f92;
    if (o != 0) {
        o->vX();
        o = arg0->f92;
        ((igObject *)o)->_refCount = (int)((int) (((igObject *)o)->_refCount - 1));
        if (((unsigned long long) ((long long) (int) ((igObject *)o)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    o = arg0->f92;
    if (o != 0) {
        ((igObject *)o)->_refCount = (int)((int) (((igObject *)o)->_refCount - 1));
        if (((unsigned long long) ((long long) (int) ((igObject *)o)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->f92 = 0;
    return arg6;
}
