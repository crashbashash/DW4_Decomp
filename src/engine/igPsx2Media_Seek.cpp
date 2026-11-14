/* Virtual slot 31 (begin) and slot 29 (end) on arg0->f16 use hidden-return temporaries, as does
 * igPsx2IopRpcConnection_Call; q = p + 4 is kept for the final read. */
#include "dw4/reflected.h"
struct R { int a; };
struct Obj { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual R v29(); virtual void d30(); virtual R v31(int); };
struct M2 { char p[12]; int *f12; };
extern "C" {
R igPsx2IopRpcConnection_Call(int, int, int *, int, int *, int, int);
int igPsx2Media_Seek(igPsx2Media *arg0, int arg1, int arg2, int arg3) {
    int *p;
    int *q;
    int s0;
    R r1 = ((Obj *)arg0->_sema)->v31(1);
    p = (int *)arg0->_commandBuffer;
    q = p + 4;
    p[0] = *(int *)((char *)((M2 *)arg0->_handlePool)->f12 + arg1 * 12 + 8);
    p[1] = arg2;
    p[2] = arg3;
    R r2 = igPsx2IopRpcConnection_Call(arg0->_connection, 4, p, 16, q, 16, 1);
    s0 = *q;
    R r3 = ((Obj *)arg0->_sema)->v29();
    return -(s0 < 0);
}
}
