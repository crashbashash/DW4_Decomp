/* Unaligned heads are staged through the scratch buffer in 0x8000-byte chunks, aligned writes go
 * directly. Each hidden-result call is read through an inline Code() so the temporaries get
 * separate slots in call order; the table index is computed after the scratch allocation. */
#include "dw4/reflected.h"
extern "C" {
int FUN_0010b7d8(int, int);
int memcpy(int, int, int);
int FUN_00300db0(void *, int, int);
}
struct R { int code; inline int Code() { return code; } };
class Q { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual R v29();
    virtual void d30();
    virtual R v31(int);
};
struct Rec { int w0; int w4; int w8; int w12; int len; };
struct Tab { int pad[3]; char *base; };
extern "C" R FUN_0032d6d0(int, int, void *, int, void *, int, int);
extern "C" int Gap__Core__igPsx2Media__vfunc_27(igPsx2Media *arg0, int arg1, int arg2, int arg3)
{
    int temp_v0;
    int var_s4;
    Rec *temp_s3;
    int *temp_s2;
    int temp_s0;
    int idx;
    int var_s1;
    int var_s0;
    var_s4 = arg2;
    ((Q *)arg0->_sema)->v31(1).Code();
    temp_s3 = (Rec *)arg0->_commandBuffer;
    temp_s2 = &temp_s3->len;
    if (var_s4 & 0x3F) {
        if (arg0->_writeBuffer == 0) {
            arg0->_writeBuffer = FUN_00300db0(arg0, 0x8000, 0x40);
        }
        idx = arg1 * 3 * 4;
        var_s1 = arg3;
        while (var_s1 != 0) {
            var_s0 = 0x8000;
            if (var_s1 < 0x8001) {
                var_s0 = var_s1;
            }
            memcpy(arg0->_writeBuffer, var_s4, var_s0);
            temp_s3->w0 = *(int *)(((Tab *)arg0->_handlePool)->base + idx + 8);
            temp_s3->w4 = arg0->_writeBuffer;
            temp_s3->w8 = var_s0;
            temp_s3->w12 = 0;
            FUN_0010b7d8(arg0->_writeBuffer, arg0->_writeBuffer + var_s0);
            FUN_0032d6d0(arg0->_connection, 7, temp_s3, 0x10, temp_s2, 0x10, 1).Code();
            temp_v0 = *temp_s2;
            if (temp_v0 != var_s0) {
                if (temp_v0 < 0) {
                    ((Q *)arg0->_sema)->v29().Code();
                    return *temp_s2;
                }
                ((Q *)arg0->_sema)->v29().Code();
                return *temp_s2 + (arg3 - var_s1);
            }
            var_s1 -= var_s0;
            var_s4 += var_s0;
        }
        ((Q *)arg0->_sema)->v29().Code();
        return arg3;
    }
    temp_s3->w0 = *(int *)(((Tab *)arg0->_handlePool)->base + arg1 * 12 + 8);
    temp_s3->w4 = var_s4;
    temp_s3->w8 = arg3;
    temp_s3->w12 = 0;
    FUN_0010b7d8(var_s4, var_s4 + arg3);
    FUN_0032d6d0(arg0->_connection, 7, temp_s3, 0x10, temp_s2, 0x10, 1).Code();
    temp_s0 = *temp_s2;
    ((Q *)arg0->_sema)->v29().Code();
    return temp_s0;
}
