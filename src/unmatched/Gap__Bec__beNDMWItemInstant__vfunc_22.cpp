#include "dw4/reflected.h"
extern "C" {
void *FUN_003a9250(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
void *beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendGroup(...);
int beNDMWItemBase_GetRecordInt(...);
void *igProperty_GetRecord(...);
extern int DAT_0051d5d0[4];
extern int DAT_0051d618[4];
extern int DAT_0051d628[4];
extern int DAT_0051d630[4];
extern int DAT_0051d640[4];
extern int DAT_0051d648[4];
extern int DAT_0051d658[4];
extern int DAT_0051d668[4];
extern int DAT_0051d670[4];
extern int DAT_0051d680[4];
extern int DAT_0051d688[4];
extern int DAT_0051d690[4];
int Gap__Bec__beNDMWItemInstant__vfunc_22(beNDMWItemInstant *arg0, beNDMWGameRam *arg1, int arg2);
}
/* matching construct: dummy-virtual class so vX() dispatches through vtable slot 22 of the random-source object */
class RandomSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned vX(); };
int Gap__Bec__beNDMWItemInstant__vfunc_22(beNDMWItemInstant *arg0, beNDMWGameRam *arg1, int arg2) {
    unsigned v;
    int obj;
    int lvl;
    int lo;
    int dmg;
    int add;
    igDataList *lst;
    int hi;
    int s3;
    int cur;
    int s2;
    int s1;
    void *rec;
    int idx;
    int a2;
    int off;
    int val;
    s3 = arg1->_messenger;
    beMessenger_SelectGroup(s3, &DAT_0051d5d0[0]);
    beMessenger_AppendInt(s3, arg2);
    beMessenger_DispatchSelected(s3, &DAT_0051d618[0]);
    s2 = (int)beMessenger_GetObject(s3, 0);
    s1 = beNDMWItemBase_GetRecordInt(arg0, arg1, &DAT_0051d628[0]);
    v = arg0->_recNo;
    switch (v) {
    case 0: {
        beMessenger_SendGroup(s3, &DAT_0051d5d0[0], &DAT_0051d630[0]);
        obj = (int)beMessenger_GetObject(s3, 0);
        lvl = *(int *)((char *)igProperty_GetRecord(obj, &DAT_0051d640[0]) + 12);
        dmg = *(int *)((char *)igProperty_GetRecord(obj, &DAT_0051d648[0]) + 12);
        beMessenger_SendGroup(s3, &DAT_0051d5d0[0], &DAT_0051d658[0]);
        s3 = (int)beMessenger_GetObject(s3, 0);
        cur = *(int *)((char *)igProperty_GetRecord(s2, &DAT_0051d668[0]) + 12);
        igProperty_GetRecord(s3, &DAT_0051d670[0]);
        if (lvl < 0x13) { lo = 0xA; hi = 0x37; }
        else if (lvl < 0x27) { lo = 0x37; hi = 0x64; }
        else if (lvl < 0x3C) { lo = 0x57; hi = 0xC3; }
        else if (lvl < 0x5E) { lo = 0xA2; hi = 0x15E; }
        else if (lvl < 0x6C) { lo = 0xE8; hi = 0x208; }
        else if (lvl < 0x90) { lo = 0x154; hi = 0x2BC; }
        else if (lvl < 0xCB) { lo = 0x1BE; hi = 0x35C; }
        else { lo = 0x236; hi = 0x488; }
        { unsigned r = ((RandomSource *)((beSystem *)arg1->_system)->_random)->vX() % (unsigned)(hi - lo); a2 = r + lo; }
        add = a2 * (dmg + 100) / 100;
        rec = igProperty_GetRecord(s2, &DAT_0051d668[0]);
        *(int *)((char *)rec + 12) = cur + add;
        arg0->_value = add;
        break;
    }
    case 1: case 2: case 3: {
        int c = *(int *)((char *)igProperty_GetRecord(s2, &DAT_0051d680[0]) + 12);
        rec = igProperty_GetRecord(s2, &DAT_0051d680[0]);
        *(int *)((char *)rec + 12) = c + s1;
        break;
    }
    default:
        break;
    case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 25: {
        idx = 0;
        switch (v - 4) {
        case 0: case 1: idx = 2; break;
        case 2: case 3: idx = 3; break;
        case 4: case 5: case 6: case 7: idx = 0; break;
        case 8: case 9: idx = 4; break;
        case 10: case 11: idx = 5; break;
        case 12: case 13: idx = 6; break;
        case 14: case 15: idx = 7; break;
        case 16: case 17: idx = 8; break;
        case 18: case 19: idx = 9; break;
        case 20: case 21: idx = 10; break;
        }
        rec = FUN_003a9250(s2, &DAT_0051d688[0]);
        off = idx * 4;
        { int el = *(int *)(((igDataList *)*(int *)((char *)rec + 12))->_data + off); val = el + s1; }
        lst = (igDataList *)*(void **)((char *)FUN_003a9250(s2, &DAT_0051d688[0]) + 12);
        if (lst->_count != 0 && idx >= 0 && idx < lst->_count) {
            *(int *)(lst->_data + off) = val;
        }
        beMessenger_SelectGroup(s3, &DAT_0051d5d0[0]);
        beMessenger_AppendInt(s3, arg2);
        beMessenger_DispatchSelected(s3, &DAT_0051d690[0]);
        return 1;
    }
    }
    return 0;
}
