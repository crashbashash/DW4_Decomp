#include "dw4/reflected.h"
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int, int); };
extern "C" {
extern int DAT_0048ac70[4];
int FUN_0017bda0(igPsx2VisualContext *arg0, int arg1, int arg2);
}
int FUN_0017bda0(igPsx2VisualContext *arg0, int arg1, int arg2) {
    int a0;
    int var_a3;
    int var_a4;
    char *s0;

    s0 = (char *)(*(int *)((char *)(arg0->_pTexList) + 16) + (arg1 * 0x88));
    if (*(int *)(s0 + 20) != 2 || *(int *)(s0 + 72) == 0) {
        return 0;
    }
    a0 = *(int *)(s0 + 0);
    var_a4 = 1;
    var_a3 = 1;
    if (a0 < 0x10000) {
        var_a4 = DAT_0048ac70[a0];
    } else if (a0 == 0x10001) {
        var_a3 = 2;
    }
    C *c = *(C **)(s0 + 52);
    c->vX(arg2, (var_a4 * (*(int *)(s0 + 32) * *(int *)(s0 + 36))) / var_a3, var_a3, var_a4);
    *(char *)(s0 + 81) = 1;
    return 1;
}
