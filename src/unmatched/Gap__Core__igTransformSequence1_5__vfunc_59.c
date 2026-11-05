#include "dw4/reflected.h"
int Gap__Core__igTransformSequence1_5__vfunc_59(igTransformSequence1_5 *arg0, int arg1) {
    if (!(arg0->_drivenChannels & arg1)) {
        return -1;
    }
    switch (arg1) {
    case 1:
        return *(unsigned char *)((char *)(arg0) + 73);
    case 2:
    case 4:
        return *(unsigned char *)((char *)(arg0) + 74);
    case 8:
        return *(unsigned char *)((char *)(arg0) + 75);
    default:
        return -1;
    }
}
