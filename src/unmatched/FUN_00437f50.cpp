#include "dw4/reflected.h"
extern "C" {
int sprintf(char *, int *, int);
int beMessenger_AppendString(int, const char *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern const char DAT_0051b218[];
extern const char DAT_0051b288[];
extern int DAT_0051b3c0[4];
extern int DAT_0051b468[4];
extern int DAT_0051b6b0[4];
extern const char DAT_0051bd60[];
void FUN_00437f50(beNDMWShopCtrlDiskSell *arg0) {
    char sp30[16];
    int temp_s0;

    temp_s0 = arg0->_maxSell - arg0->_retCode;
    sprintf(sp30, &DAT_0051b468[0], temp_s0);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051bd60[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b218[0]);
    beMessenger_AppendString(arg0->_messenger, sp30);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b6b0[0]);
    sprintf(sp30, &DAT_0051b468[0], temp_s0 * arg0->_tanka);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051bd60[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b288[0]);
    beMessenger_AppendString(arg0->_messenger, sp30);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b6b0[0]);
}
}
