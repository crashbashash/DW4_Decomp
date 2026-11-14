#include "dw4/reflected.h"
struct R { int v; R() {} R(const R &o) : v(o.v) {} };
struct VC {
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
 virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
 virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
 virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual R vY();
 virtual void d30();
 virtual R vX(int);
};
struct W { int f0; int f4; int f8; int fc; int f10; };
struct T { int p0; int p4; int p8; char *rows; };
extern "C" {
R igPsx2IopRpcConnection_Call(int, int, W *, int, int *, int, int);
int igPsx2Media_Tell(igPsx2Media *arg0, int arg1);
}
/* matching construct: _sema/_commandBuffer/_handlePool are 4-byte reference fields; the casts give the typed views (no layout effect) */
int igPsx2Media_Tell(igPsx2Media *arg0, int arg1) {
    W *w;
    R r1 = ((VC *)arg0->_sema)->vX(1);
    w = (W *)arg0->_commandBuffer;
    w->f0 = *(int *)(((T *)arg0->_handlePool)->rows + arg1 * 12 + 8);
    w->f4 = 0;
    w->f8 = 1;
    arg1 = (int)&w->f10;
    R r2 = igPsx2IopRpcConnection_Call(arg0->_connection, 4, w, 16, (int *)arg1, 16, 1);
    arg1 = *(int *)arg1;
    R r3 = ((VC *)arg0->_sema)->vY();
    return arg1;
}
