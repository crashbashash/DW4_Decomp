#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00588f38[4];
extern int DAT_00589208[4];
void Gap__Bec__beDemoManager__vfunc_23(beDemoManager *arg0);
}

void Gap__Bec__beDemoManager__vfunc_23(beDemoManager *arg0) {
    arg0->_messenger = FUN_00236f80(arg0->_insight, DAT_00588f38[0]);
    arg0->_lua = FUN_00236f80(arg0->_insight, DAT_00589208[0]);
}
