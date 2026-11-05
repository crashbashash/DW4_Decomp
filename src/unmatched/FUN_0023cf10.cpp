#include "dw4/reflected.h"
struct FL { char pad[2]; unsigned char b0 : 1; unsigned char b1 : 1; unsigned char b2 : 1; unsigned char b3 : 1; unsigned char b4 : 1; unsigned char b5 : 1; unsigned char b6 : 1; unsigned char b7 : 1; };
/* matching construct: byte-wide view of the flag bits inside igObject::_refCount */
union U4 { int v; FL fl; };
struct RefCountFlags { char pad0[4]; U4 u; };
struct S_arg0 { char pad0[4]; int f4; int f8; };
extern "C" {
void *FUN_00241700(...);
int lua_tag(...);
int lua_pushnil(...);
int lua_pushusertag(...);
int lua_settag(...);
extern int DAT_00498668[4];
void FUN_0023cf10(struct S_arg0 *arg0, int arg1, struct RefCountFlags *arg2, int arg3);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void FUN_0023cf10(struct S_arg0 *arg0, int arg1, struct RefCountFlags *arg2, int arg3) {
    void *var_s3;

    if (arg2 == 0) {
        lua_pushnil(arg1);
        return;
    }
    var_s3 = (void *)(arg0->f8);
    if (var_s3 != 0) {
        if (arg0->f4 != 0) {
            var_s3 = (void *)(FUN_00241700(((DW4VC_88_0 *)arg2)->vX()));
        }
        if (arg3 == 0) {
            lua_pushusertag(arg1, arg2, *(int *)((char *)(var_s3) + 40));
        } else if (arg3 == 1) {
            lua_pushusertag(arg1, arg2, *(int *)((char *)(var_s3) + 44));
        } else {
            lua_pushusertag(arg1, arg2, -1);
            if (lua_tag(arg1, -1) == 0) {
                lua_settag(arg1, *(int *)((char *)(var_s3) + 44));
            }
        }
    } else if (arg0->f4 != 0) {
        lua_pushusertag(arg1, arg2, DAT_00498668[0]);
    }
    if (arg0->f4 != 0) {
        if (arg2->u.fl.b7 == 0) {
            arg2->u.fl.b7 = 1;
            ((igObject *)arg2)->_refCount = ((igObject *)arg2)->_refCount + 1;
        }
    }
}
