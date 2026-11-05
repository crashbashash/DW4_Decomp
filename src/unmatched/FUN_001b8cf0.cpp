#include "dw4/reflected.h"
extern "C" {
int igMatrix44f_SetIdentity(...);
int FUN_001b8ba0(...);
int Matrix44_Copy(...);
extern int DAT_0055efe8[4];
extern int DAT_00561918[4];
void FUN_001b8cf0(igCommonTraversal *arg0, char *arg1);
}
class VC_104a { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();  virtual int vX(); };
class VC_156b { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();  virtual int vX(int); };
void FUN_001b8cf0(igCommonTraversal *arg0, char *arg1) {
    igAttrStackManager *a2;
    igAttrStack *a0;
    int n;
    int v;
    int a1;
    int k;
    char *dst;
    ((VC_156b *)arg1)->vX(((VC_104a *)arg0)->vX());
    a2 = (igAttrStackManager *)arg0->_attrStack;
    a0 = ((igAttrStack **)((igAttrStackList *)a2->_attrStacks)->_data)[((int *)a2->_attrStackIndexTable)[((igMetaObject *)DAT_0055efe8[0])->_id]];
    n = a0->_count;
    a1 = 0;
    if (n == 0) { v = 0; } else { k = n - 1; v = ((int *)a0->_data)[k]; }
    if (v != 0) { a1 = v + 12; }
    dst = arg1 + ((igMetaObject *)DAT_00561918[0])->_id;
    if (a1 != 0) {
        Matrix44_Copy(dst, a1, a2);
    } else {
        igMatrix44f_SetIdentity(dst, a1, a2);
    }
    FUN_001b8ba0(arg0, arg1);
}
