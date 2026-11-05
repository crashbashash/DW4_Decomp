#include "dw4/reflected.h"
extern "C" {
int FUN_002d63e0(...);
void *FUN_002d65e0(...);
int ObjectList_AppendRetained(...);
void *igMetaObject_CreateInstance(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void *FUN_002d64c0(igVisualContext *arg0);
}
class DW4VC_112_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int); };
class DW4VC_116_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int); };
void *FUN_002d64c0(igVisualContext *arg0) {
    int temp_v0;
    igObject *var_s0;

    temp_v0 = FUN_002d63e0();
    if (temp_v0 == 0) {
        return 0;
    }
    var_s0 = (igObject *)(FUN_002d65e0(arg0, temp_v0));
    if (var_s0 == 0) {
        var_s0 = (igObject *)(igMetaObject_CreateInstance(temp_v0, igObject_GetAllocator(arg0)));
        if (var_s0 != 0) {
            if (((DW4VC_112_1 *)(((char *)(var_s0) + 0)))->vX((int)(arg0)) == 0) {
                var_s0->_refCount = var_s0->_refCount - 1;
                if ((var_s0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(var_s0);
                }
                var_s0 = (igObject *)(0);
            } else {
                ObjectList_AppendRetained(arg0->_pExtInstances, var_s0);
                var_s0->_refCount = var_s0->_refCount - 1;
                if ((var_s0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(var_s0);
                }
                ((DW4VC_116_1 *)(((char *)(var_s0) + 0)))->vX((int)(arg0));
            }
        }
    }
    return var_s0;
}
