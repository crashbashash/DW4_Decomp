#include "dw4/reflected.h"
extern "C" {
int beMessenger_SelectGroup(int, void *);
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, void *);
void *beMessenger_GetObject(int, int);
void *igProperty_GetRecordFolder(void *, void *);
int FUN_00236f80(int, int);
int beNDMWItemBase_GetRecordBool(void *, int, void *);
int List_Resize(void *, int, int);
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_00519c00[4];
extern int DAT_0051a0c8[4];
extern int DAT_0051a0e8[4];
extern int DAT_0051a0f0[4];
extern int DAT_0058b028[4];
int FUN_004191f0(beNDMWStatusCtrlD0 *arg0);
}
int FUN_004191f0(beNDMWStatusCtrlD0 *arg0) {
    int n;
    void *obj;
    int idx;
    int pages;
    bool ok;
    int rem;
    igObjectList *fold;
    int k;
    igDataList *out;
    int shown;
    int t; int a; unsigned char b1; unsigned char b2; unsigned char w;
    beNDMWItemBase *rec;
    beMessenger_SelectGroup(arg0->_messenger, DAT_00519ba0);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00519ba8);
    obj = beMessenger_GetObject(arg0->_messenger, 0);
    if (arg0->_isBankFolder != 0) {
        int tmp = ((int *)igProperty_GetRecordFolder(obj, DAT_0051a0c8))[3];
        fold = (igObjectList *)tmp;
    } else {
        int tmp = ((int *)igProperty_GetRecordFolder(obj, DAT_00519c00))[3];
        fold = (igObjectList *)tmp;
    }
    if (fold->_count % 12 != 0) {
        pages = fold->_count / 12 + 1;
    } else {
        pages = fold->_count / 12;
    }
    arg0->_maxPage = pages;
    rem = fold->_count - arg0->_nowPage * 12;
    if (rem >= 12) {
        shown = 12;
    } else {
        shown = rem % 12;
    }
    ((igDataList *)arg0->_decideList)->_count = 0;
    for (idx = 0; idx < shown; idx++) {
        rec = *(beNDMWItemBase **)(fold->_data + (arg0->_nowPage * 12 + idx) * 4);
        ok = true;
        if (((igDataList *)arg0->_kindList)->_count > 0) {
            ok = false;
            for (k = 0; k < ((igDataList *)arg0->_kindList)->_count; k++) {
                t = *(int *)(((igDataList *)arg0->_kindList)->_data + k * 4);
                if (t == 3) {
                    if (rec->_kindNo == 3) {
                        a = FUN_00236f80(arg0->_insight, DAT_0058b028[0]);
                        b1 = beNDMWItemBase_GetRecordBool(rec, a, DAT_0051a0e8);
                        b2 = beNDMWItemBase_GetRecordBool(rec, a, DAT_0051a0f0);
                        switch (arg0->_isAbType) {
                        default: w = 1; break;
                        case 0: w = b1; break;
                        case 1: w = b2; break;
                        }
                        if (w == 1) { ok = true; break; }
                    }
                } else if ((t == 0 && rec->_kindNo == 0) || (t == 1 && rec->_kindNo == 1) || (t == 2 && rec->_kindNo == 2)) {
                    ok = true;
                    break;
                }
            }
        }
        if (arg0->_isEquipDisable != 0 && rec->_isEquip != 0) ok = false;
        if (arg0->_isUnknownDisable != 0) {
            if ((rec->_kindNo == 0 && rec->_recNo == 276) || (rec->_kindNo == 1 && rec->_recNo == 31) || (rec->_kindNo == 2 && rec->_recNo == 44)) ok = false;
        }
        if (arg0->_isUnknownEnable != 0) {
            if ((rec->_kindNo == 0 && rec->_recNo == 276) || (rec->_kindNo == 1 && rec->_recNo == 31) || (rec->_kindNo == 2 && rec->_recNo == 44)) ok = true;
            else ok = false;
        }
        out = (igDataList *)arg0->_decideList;
        n = out->_count;
        if (n < out->_capacity) out->_count = n + 1;
        else List_Resize(out, n + 1, 1);
        *(unsigned char *)(n + out->_data) = ok;
    }
    if (arg0->_maxPage == 0) arg0->_maxPage = 1;
    if (shown == 0) shown = 1;
    return shown;
}
