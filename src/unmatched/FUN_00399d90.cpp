#include "dw4/reflected.h"
class V92;
class V92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual unsigned char vX(void *, int); };
class V96;
class V96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned char vX(void *, int); };
extern "C" {
unsigned char FUN_00399d90(beModelCtrlSubComBase *arg0, beBaseInfoRam *arg1);
}
unsigned char FUN_00399d90(beModelCtrlSubComBase *arg0, beBaseInfoRam *arg1) {
    float temp_f1;
    unsigned char var_v0;

    temp_f1 = arg0->_runFrame + ((beSystem *)((beBaseInfoManager *)arg1->_parentManager)->_system)->_frameTimeF;
    arg0->_runFrame = temp_f1;
    var_v0 = 1;
    if (arg0->_isOneSet == 0) {
        if (!(temp_f1 < arg0->_startFrame)) {
            arg0->_isOneSet = 1;
            var_v0 = ((V92 *)arg0)->vX(arg1, 1);
        }
    } else {
        var_v0 = ((V96 *)arg0)->vX(arg1, 1);
    }
    return var_v0;
}