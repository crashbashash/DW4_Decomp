#include "dw4/reflected.h"
struct igGroupMaskView { char p[28]; igNodeList *_childList; igBitMask *_mask; };
extern "C" {
int FUN_001e04c0(void *a, int b);
int FUN_001b7b90(void *t, void *arg);
}
int FUN_001b7b90(void *t, void *arg) {
    int r;
    int i;
    igGroupMaskView *n;
    int count;
    igBitMask *mask;
    n = (igGroupMaskView *)arg;
    mask = n->_mask;
    if (n->_childList) count = n->_childList->_count; else count = 0;
    for (i = 0; i < count; i++) {
        int m = 1 << (i & 31);
        if (m & ((int *)mask->_data)[(unsigned int)i >> 5]) {
            r = FUN_001e04c0(t, ((int *)n->_childList->_data)[i]);
            if (r == 1) break;
            if (r == 2) return 2;
        }
    }
    return 0;
}
