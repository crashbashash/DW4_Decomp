#include "dw4/reflected.h"
extern "C" {
float __floatdisf(int);
int beMessenger_AppendFloat(int, float);
int beMessenger_AppendString(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_SelectReceivers(int, int *, int, int);
int igStrCmp(int *, int);
extern int DAT_004e0858[4];
extern int DAT_0050f778[4];
extern int DAT_0050f788[4];
}
/* arg1 context: +12 holds the owning info (sectl.c context+0xc); class not identified */
struct ContextView { char p[12]; int f12; };
/* arg2 message record: +12 model name, +16 slot, +20 action name (recovered/frontend/sectl.c) */
struct SeMessageView { char p[12]; int f12; int f16; int f20; };
/* matching construct: (int *)/(beSeInfoData *) casts convert between the 4-byte reference fields and typed pointers */
extern "C" {
int Gap__Bec__beSeCtl__vfunc_34(beSeCtl *arg0, struct ContextView *arg1, struct SeMessageView *arg2);
}
int Gap__Bec__beSeCtl__vfunc_34(beSeCtl *arg0, struct ContextView *arg1, struct SeMessageView *arg2) {
    int res;
    int s5;
    beSeDataList *l2;
    int j;
    int sh;
    beBaseInfoDataList *l1;
    beSeInfo *info;
    beSeInfoData *row;
    int i;
    int off;
    int s7;
    int s8;
    beSeData *it;
    int *p;



    res = -1;
    s7 = arg2->f20;
    s5 = arg2->f12;
    s8 = arg2->f16;
    info = (beSeInfo *)arg1->f12;
    l1 = (beBaseInfoDataList *)info->_dataList;
    i = 0;
    if (0 < l1->_count) {
        off = 0;
        do {
            row = (beSeInfoData *)*(int *)((char *)l1->_data + off);
            p = (int *)row->_name;
            if (igStrCmp(p != 0 ? p : &DAT_004e0858[0], s5) == 0) {
                res = i;
            }
            i += 1;
            off += 4;
        } while (i < l1->_count);
    }
    if (res == -1) {
        return 1;
    }
    row = ((beSeInfoData **)l1->_data)[res];
    l2 = (beSeDataList *)row->_actionList;
    j = 0;
    if (0 < l2->_count) {
        off = 0;
        do {
            it = *(beSeData **)((char *)l2->_data + off);
            p = (int *)it->_name;
            if (igStrCmp(p != 0 ? p : &DAT_004e0858[0], s7) == 0) {
                sh = it->_delay;
                beMessenger_SelectReceivers(arg0->_messenger, &DAT_0050f778[0], s5, s8);
                beMessenger_AppendString(arg0->_messenger, it->_sound);
                beMessenger_AppendFloat(arg0->_messenger, __floatdisf(sh));
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_0050f788[0]);
            }
            j += 1;
            off += 4;
        } while (j < l2->_count);
    }
    return 1;
}
