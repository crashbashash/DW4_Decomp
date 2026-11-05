#include "dw4/reflected.h"

/* matching construct: dummy-virtual view of beNDMWPanelObjectWaza so the call
 * through slot 21 (Gap__Bec__beNDMWPanelObjectWaza__vfunc_21) compiles to the
 * retail vtable load; the data fields are reached through the reflected struct. */
class WazaPanelShim {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void v21();
};
/* property records returned by the igProperty lookups (no reflected class) */
struct Rec { int p[3]; igObjectList *f12; };
struct Fld { int p[3]; int f12; };
extern "C" {
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, void *);
int beNDMWItemBase_GetRecordInt(beNDMWItemBase *, beNDMWPanelWaza *, void *);
Fld *igProperty_GetRecord(int, void *);
Rec *igProperty_GetRecordFolder(int, void *);
extern int DAT_005159f0[4];
extern int DAT_005159f8[4];
extern int DAT_00515a08[4];
extern int DAT_00515a20[4];
int FUN_003d08f0(beNDMWPanelWaza *arg0, beNDMWPanelWazaInfoRam *arg1) {
    igObjectList *s5 = 0;
    int s4 = 0;
    int s3 = 0;
    beNDMWPanelWazaInfoWork *s2 = 0;
    int s1 = 0;
    int s0 = 0;
    s2 = (beNDMWPanelWazaInfoWork *)arg1->_work;
    if (((beNDMWPanelObjectWaza *)s2->_panelWaza)->_isNoHealing != 0) {
        return 0;
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_005159f0[0]);
    beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159f8[0]);
    int o = beMessenger_GetObject(arg0->_messenger, 0);
    s1 = igProperty_GetRecord(o, &DAT_00515a20[0])->f12;
    s5 = igProperty_GetRecordFolder(o, &DAT_00515a08[0])->f12;
    s4 = s5->_count;
    s3 = s4 - 1;
    s0 = s3 * 4;
    if (s3 >= 0) {
        do {
            beNDMWItemBase *it = ((beNDMWItemBase **)(s5->_data + s0))[0];
            int t = it->_recNo;
            s4 -= 1;
            if (t >= 40 && t < 50 && s1 >= beNDMWItemBase_GetRecordInt(it, arg0, &DAT_00515a20[0])) {
                int r = s4 - 3;
                if (r < 0) {
                    r = 0;
                } else {
                    s4 -= r;
                }
                ((WazaPanelShim *)s2->_panelWaza)->v21();
                ((beNDMWPanelObjectWaza *)s2->_panelWaza)->_cursor = s4;
                ((beNDMWPanelObjectWaza *)s2->_panelWaza)->_offset = r;
                ((beNDMWPanelObjectWaza *)s2->_panelWaza)->_isEmg = 1;
                return 1;
            }
            s3 -= 1;
            s0 -= 4;
        } while (s3 >= 0);
    }
    return 0;
}
}
