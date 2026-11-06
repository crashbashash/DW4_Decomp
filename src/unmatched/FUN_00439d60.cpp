#include "dw4/reflected.h"
extern "C" {
int FUN_00236f80(...);
void *FUN_003a9250(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beNDMWItemBase_GetRecordInt(...);
void *igProperty_GetRecord(...);
extern int DAT_0051b398[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b5a0[4];
extern int DAT_0051bac0[4];
extern int DAT_0051bdc8[4];
extern int DAT_0051bdd0[4];
extern int DAT_0051bdd8[4];
extern int DAT_0051bde8[4];
extern int DAT_0058b028[4];
}
struct Rec { char pad[12]; int f12; };
/* matching construct: the retail bool result (daddiu) comes from an inline member function with early returns */
struct SalesChk {
    static bool Chk(beNDMWShopCtrlSales *self, beNDMWItemBase *arg1, int obj) {
        int rec;
        int s3, s0;
        igIntList *l;
        int a, b;
        if (arg1 == 0) return false;
        if (arg1->_kindNo == 3) return true;
        rec = FUN_00236f80(self->_insight, DAT_0058b028[0]);
        if (arg1->_kindNo == 0) {
            int sh = ((Rec *)igProperty_GetRecord(obj, &DAT_0051bac0[0]))->f12;
            s3 = (1 << sh) & beNDMWItemBase_GetRecordInt(arg1, rec, &DAT_0051bdc8[0]);
            l = (igIntList *)((Rec *)FUN_003a9250(obj, &DAT_0051bdd0[0]))->f12;
            a = beNDMWItemBase_GetRecordInt(arg1, rec, &DAT_0051bdd0[0]);
            b = beNDMWItemBase_GetRecordInt(arg1, rec, &DAT_0051bdd8[0]);
            if (s3 != 0 && ((int *)l->_data)[a] >= b) return true;
            return false;
        } else if (arg1->_kindNo == 1 || arg1->_kindNo == 2) {
            s0 = ((Rec *)igProperty_GetRecord(obj, &DAT_0051b5a0[0]))->f12;
            if (s0 >= beNDMWItemBase_GetRecordInt(arg1, rec, &DAT_0051bde8[0])) return true;
            return false;
        }
        return false;
    }
};
extern "C" bool FUN_00439d60(beNDMWShopCtrlSales *arg0, beNDMWItemBase *arg1);
bool FUN_00439d60(beNDMWShopCtrlSales *arg0, beNDMWItemBase *arg1) {
    int obj;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    obj = beMessenger_GetObject(arg0->_messenger, 0);
    return SalesChk::Chk(arg0, arg1, obj);
}
