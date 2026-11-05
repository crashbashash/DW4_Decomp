/* 0x003cc3d0 - 176 bytes. Fill a list with one value (loop unrolled by 8); alternate compiler -O3,p.
 * Receiver is an igIntList (_count +8, _data +16): its caller passes the beNDMWPanelWazaInfoWork _textColorList. */
#include "dw4/reflected.h"
void FUN_003cc3d0(igIntList *arg0, int *arg1) {
    int n = arg0->_count;
    int *d = (int *)arg0->_data;
    int i;
    for (i = 0; i < n; i++) {
        d[i] = *arg1;
    }
}
