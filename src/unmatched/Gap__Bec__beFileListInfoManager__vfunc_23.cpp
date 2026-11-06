#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(int, int);
extern int DAT_00587d08[4];
extern int DAT_00588f38[4];
extern int DAT_0058c790[4];
void Gap__Bec__beFileListInfoManager__vfunc_23(beFileListInfoManager *arg0);
}

void Gap__Bec__beFileListInfoManager__vfunc_23(beFileListInfoManager *arg0) {
    arg0->_system = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
    arg0->_messenger = FUN_00236f80(arg0->_insight, DAT_00588f38[0]);
    arg0->_sceneInfoManager = FUN_00236f80(arg0->_insight, DAT_0058c790[0]);
}
