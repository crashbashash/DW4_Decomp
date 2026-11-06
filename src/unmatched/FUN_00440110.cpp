#include "dw4/reflected.h"
extern "C" {
int sprintf(char *, int *, int);
int strlen(char *);
int beMessenger_AppendString(int, const char *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectGroup(int, int *);
extern int DAT_0051c6e0[4];
extern int DAT_0051c6e8[4];
extern int DAT_0051c6f0[4];
extern int DAT_0051c710[4];
extern const char DAT_0051c740[];
extern int DAT_0051c750[4];
extern const char DAT_0051c780[];
extern int DAT_0051c788[4];
extern const char DAT_0051c790[];
void FUN_00440110(beNDMWShopCtrlEditBit *arg0, int arg1, int arg2) {
    char buf[16];
    char tmp[12];
    char ch[2];
    int *tbl;
    int n;
    int i;
    int j;

    switch (arg1) {
    default:
        tbl = DAT_0051c750;
        break;
    case 1:
        tbl = DAT_0051c710;
        break;
    }
    i = 0;
    do {
        sprintf(buf, tbl, i);
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
        beMessenger_AppendString(arg0->_messenger, DAT_0051c740);
        beMessenger_AppendString(arg0->_messenger, buf);
        beMessenger_AppendString(arg0->_messenger, DAT_0051c780);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c788);
        i += 1;
    } while (i < 7);
    sprintf(tmp, DAT_0051c6e0, arg2);
    n = strlen(tmp);
    j = n - 1;
    ch[1] = 0;
    if (j > -1) {
        do {
            sprintf(buf, tbl, j);
            ch[0] = tmp[(n - 1) - j];
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c740);
            beMessenger_AppendString(arg0->_messenger, buf);
            beMessenger_AppendString(arg0->_messenger, ch);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c6f0);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c740);
            beMessenger_AppendString(arg0->_messenger, buf);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c790);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c788);
            j -= 1;
        } while (j > -1);
    }
}
}
