#include "dw4/reflected.h"
extern "C" {
int beMessenger_SendNamed(int, int *, int, int, int *);
extern int DAT_0050f468[4];
extern int DAT_0050f498[4];
void Gap__Bec__beModelCtrlSCEffect__vfunc_23(beModelCtrlSCEffect *arg0, void *arg1);
}
void Gap__Bec__beModelCtrlSCEffect__vfunc_23(beModelCtrlSCEffect *arg0, void *arg1) {
    int temp_a3;

    if (arg0->_isOneSet != 0) {
        temp_a3 = arg0->_geneRamNo;
        if (temp_a3 != -1) {
            beMessenger_SendNamed(*(int *)((char *)(*(int *)((char *)(arg1) + 16)) + 20), &DAT_0050f468[0], arg0->_modelName, temp_a3, &DAT_0050f498[0]);
        }
    }
}
