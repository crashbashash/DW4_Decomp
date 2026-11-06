#include "dw4/reflected.h"
int igObject_InitHeader();
extern int DAT_00524950[4];
extern int DAT_00528a90[4];
extern int DAT_00528dd0[4];
void *FUN_0019acf0(igGroup *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&DAT_00524950[0]);
    arg0->_name = 0;
    arg0->_vtable = (int)(&DAT_00528a90[0]);
    arg0->_bound = 0;
    arg0->_parentList = 0;
    arg0->_vtable = (int)(&DAT_00528dd0[0]);
    arg0->_childList = 0;
    return arg0;
}
