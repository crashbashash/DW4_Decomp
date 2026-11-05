#include "dw4/reflected.h"
extern "C" {
extern int DAT_0058c448[4];
extern int DAT_0058c450[4];
extern int DAT_0058c458[4];
extern int DAT_0058c460[4];
void Gap__Gui__igGuiComponentController__vfunc_24(igGuiComponentController *arg0, void *arg1);
}
class DW4VC_104_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
class DW4VC_108_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int); };
class DW4VC_112_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int, int); };
class DW4VC_116_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, int); };
class DW4VC_120_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(int, int); };
class DW4VC_124_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int, int); };
class DW4VC_128_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int); };
class DW4VC_132_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int, int); };
void Gap__Gui__igGuiComponentController__vfunc_24(igGuiComponentController *arg0, void *arg1) {
    int temp_a1;
    igGuiComponentModel *temp_a2;

    temp_a1 = *(int *)((char *)(arg1) + 8);
    temp_a2 = (igGuiComponentModel *)(arg0->_model);
    if (temp_a1 == DAT_0058c448[0]) {
        if (temp_a2->_enabled != 0) {
            ((DW4VC_104_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_108_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c450[0]) {
        if (temp_a2->_hasFocus != 0) {
            ((DW4VC_112_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_116_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c458[0]) {
        if (temp_a2->_mouseOver != 0) {
            ((DW4VC_120_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_124_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
        return;
    }
    if (temp_a1 == DAT_0058c460[0]) {
        if (temp_a2->_pushed != 0) {
            ((DW4VC_128_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
            return;
        }
        ((DW4VC_132_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2));
    }
}
