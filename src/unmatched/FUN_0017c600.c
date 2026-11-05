#include "dw4/reflected.h"
extern int DAT_00560a34[4];
extern int DAT_00560a38[4];
struct P { char pad[16]; char *e; };
void FUN_0017c600(struct igPsx2VisualContext *arg0, int arg1, int arg2, int arg3) {
    int temp_v1;
    temp_v1 = arg1 * 0x88;
    if (arg2 == *(int *)(((struct P *)arg0->_pTexList)->e + temp_v1 + 12)) {
        DAT_00560a34[0] += 1;
    }
    if (arg3 == *(int *)(((struct P *)arg0->_pTexList)->e + temp_v1 + 16)) {
        DAT_00560a38[0] += 1;
    }
    *(int *)(((struct P *)arg0->_pTexList)->e + temp_v1 + 12) = arg2;
    *(int *)(((struct P *)arg0->_pTexList)->e + temp_v1 + 16) = arg3;
    *(char *)(((struct P *)arg0->_pTexList)->e + temp_v1 + 80) = 1;
}
