/* Vertex element set; 4-byte value passed in a union (int store / bytewise store), virtual type
 * test; alternate compiler. */
#include "dw4/reflected.h"
extern "C" {
void *igVertexArray2__FindVertexData(...);
extern int DAT_00561098[4];
extern int DAT_00586858[4];
struct B4 { unsigned char b[4]; };
union U { int i; B4 b; };
void Gap__Core__igVertexArray2Helper__vfunc_40(igVertexArray2Helper *arg0, int arg1, U arg2);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct T : VC { int f4; int f8; int f12; int *f16; };
struct S { char pad[12]; T *f12; };
void Gap__Core__igVertexArray2Helper__vfunc_40(igVertexArray2Helper *arg0, int arg1, U arg2) {
    int temp_s1;
    S *temp_v0;
    int temp_s1_2;
    temp_v0 = (S *)(igVertexArray2__FindVertexData(arg0->_vertexArray, 2, 0));
    temp_s1 = DAT_00586858[0];
    if (temp_s1 == temp_v0->f12->vX()) {
        T *a = temp_v0->f12;
        int v1 = a->f8;
        if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
            a->f16[arg1] = arg2.i;
        }
    } else {
        temp_s1_2 = DAT_00561098[0];
        if (temp_s1_2 == temp_v0->f12->vX()) {
            T *a = temp_v0->f12;
            int v1 = a->f8;
            if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
                unsigned char *d = (unsigned char *)(a->f16 + arg1);
                d[0] = arg2.b.b[0];
                d[1] = arg2.b.b[1];
                d[2] = arg2.b.b[2];
                d[3] = arg2.b.b[3];
            }
        }
    }
}
