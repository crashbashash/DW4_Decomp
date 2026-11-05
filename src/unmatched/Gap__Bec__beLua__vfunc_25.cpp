#include "dw4/reflected.h"
extern "C" {
int igObject_IsKindOf(int, int);
int ObjectList_AppendRetained(int, int);
extern int DAT_005891c0[4];
int Gap__Bec__beLua__vfunc_25(beLua *arg0, int arg1);
}
int Gap__Bec__beLua__vfunc_25(beLua *arg0, int arg1) {
    if (igObject_IsKindOf(arg1, DAT_005891c0[0]) != 0) {
        ObjectList_AppendRetained(arg0->_infoList, arg1);
        return 1;
    }
    return 0;
}
