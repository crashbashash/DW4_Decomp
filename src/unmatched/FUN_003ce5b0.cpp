#include "dw4/reflected.h"
extern "C" {

int FUN_003ce4c0(beNDMWPanelObject *, int *);
int FUN_003ce500(beNDMWPanelObject *, int *, int *, int *, int);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern int DAT_004cc690[][4];
extern int DAT_005159a0[4];
extern int DAT_005159b0[4];
extern int DAT_005159c0[4];
extern int DAT_005159c8[4];
extern int DAT_005159d8[4];
void FUN_003ce5b0(beNDMWPanelObject *arg0, int arg1, int arg2) {
    int sp40[3];
    int v;
    int k;

    switch (arg0->_listKazu) {
    case 0:
    case 1:
    case 2:
        v = 2;
        break;
    case 3:
        v = 1;
        break;
    default:
        v = 0;
        break;
    }
    arg0->_lineMode = v;
    if (arg1 != 0) {
        FUN_003ce4c0(arg0, sp40);
        FUN_003ce500(arg0, &DAT_005159a0[0], &DAT_005159b0[0], sp40, DAT_004cc690[arg0->_page][v]);
    } else {
        FUN_003ce500(arg0, &DAT_005159a0[0], (int *)DAT_004cc690[arg0->_page][v], 0, 0);
    }
    if (!(arg2 & 0xFF)) {
        beMessenger_SelectGroup(arg0->_messenger, &DAT_005159c0[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005159c8[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159d8[0]);
    }
}
}
