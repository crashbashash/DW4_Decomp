#include "dw4/reflected.h"
struct V3 { float x, y, z; };
struct A { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual unsigned v34(); char pad[28]; unsigned f32; };
extern "C" {
igVertexData *igVertexArray2__FindVertexData(igVertexArray2 *, int, int);
void FUN_001b23b0(igVertexArray2 **, A *);
int igObject_IsKindOf(igVec3fList *, int);
void igObject_Destroy(igVertexArray2 *);
extern int DAT_005610b8[4];
extern float GPR_00554914;
extern float GPR_00554918;
void FUN_001b21d0(A *arg0, V3 *arg1, V3 *arg2);
}
/* matching construct: the receiver class is not established (the +12 vertex array and +32 index base are accessed through FUN_001b23b0 / f32 below), so it keeps a local layout; _objList data, _data and the vertex array reference are 4-byte handles, so the handle and the array stay ONE variable */
void FUN_001b21d0(A *arg0, V3 *arg1, V3 *arg2) {
    igVertexArray2 *sp7C;
    igVec3fList *s3;
    unsigned s4, s5;
    V3 *v;
    arg1->x = arg1->y = arg1->z = GPR_00554914;
    arg2->x = arg2->y = arg2->z = GPR_00554918;
    FUN_001b23b0(&sp7C, arg0);
    s3 = (igVec3fList *)igVertexArray2__FindVertexData(sp7C, 1, 0);
    if (sp7C != 0) {
        sp7C->_refCount = sp7C->_refCount - 1;
        if (((unsigned long long)(long long)(int)sp7C->_refCount & 0x7fffffULL) == 0) igObject_Destroy(sp7C);
    }
    if (s3 != 0) {
        s3 = (igVec3fList *)((igVertexData *)s3)->_data;
        if (s3 != 0 && igObject_IsKindOf(s3, DAT_005610b8[0]) != 0) {
            s3 = (igVec3fList *)s3;
        } else {
            s3 = 0;
        }
        s4 = arg0->f32;
        while (s5 = arg0->f32, s4 < s5 + arg0->v34()) {
            v = (V3 *)((char *)s3->_data + s4 * 12);
            if (!(arg1->x <= v->x)) arg1->x = v->x;
            if (!(arg1->y <= v->y)) arg1->y = v->y;
            if (!(arg1->z <= v->z)) arg1->z = v->z;
            v = (V3 *)((char *)s3->_data + s4 * 12);
            if (arg2->x < v->x) arg2->x = v->x;
            if (arg2->y < v->y) arg2->y = v->y;
            if (arg2->z < v->z) arg2->z = v->z;
            s4++;
        }
    }
}
