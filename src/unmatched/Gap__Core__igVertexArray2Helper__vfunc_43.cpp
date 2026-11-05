#include "dw4/reflected.h"
extern "C" {
struct T; struct S;
void *igVertexArray2__FindVertexData(...);
int FUN_00193540(...);
extern int DAT_00561098[4];
extern int DAT_00586858[4];
void Gap__Core__igVertexArray2Helper__vfunc_43(igVertexArray2Helper *arg0, int arg1, int arg2);
}
struct T { char pad[16]; int *f16; };
struct S { char pad[12]; T *f12; };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void Gap__Core__igVertexArray2Helper__vfunc_43(igVertexArray2Helper *arg0, int arg1, int arg2) {
    int temp_s1;
    S *temp_v0;
    int temp_s1_2;

    temp_v0 = (S *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 2, 0));
    temp_s1 = DAT_00586858[0];
    if (temp_s1 == ((DW4VC_88_0 *)(temp_v0->f12))->vX()) {
        FUN_00193540(arg2, 1, temp_v0->f12->f16[arg1]);
        return;
    }
    temp_s1_2 = DAT_00561098[0];
    if (temp_s1_2 == ((DW4VC_88_0 *)(temp_v0->f12))->vX()) {
        FUN_00193540(arg2, 1, temp_v0->f12->f16[arg1]);
    }
}
