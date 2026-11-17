#include "dw4/core/igObject.h"
extern "C" {
extern int DAT_00524950[4];
extern int DAT_0052cf80[4];
void *FUN_00458630(void *arg0) {
    igObject_InitHeader((igObject *)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00524950[0]);
    *(int *)((char *)(arg0) + 8) = 0;
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_0052cf80[0]);
    return arg0;
}
}
