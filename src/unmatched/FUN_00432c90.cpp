#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectReceivers(int, int *, int, int);
extern int DAT_0051b398[4];
extern int DAT_0051b3a0[4];
void FUN_00432c90(beNDMWShopCtrlDigilabo *arg0) {
    int i;
    for (i = 0; i < ((igIntList *)arg0->_playerNoList)->_count; i++) {
        beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
        beMessenger_AppendInt(arg0->_messenger, ((int *)((igIntList *)arg0->_playerNoList)->_data)[i]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
    }
}
} /* extern "C" */
