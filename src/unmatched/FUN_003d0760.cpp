#include "dw4/reflected.h"

/* matching construct: dummy-virtual view of beNDMWPanelObjectItem so the call
 * through slot 21 compiles to the retail vtable load; the data fields are
 * reached through the reflected struct. */
class ItemPanelShim {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void v21();
};
/* property record returned by the igProperty lookup (no reflected class) */
struct Rec { int p[3]; igObjectList *f12; };
extern "C" {
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, void *);
Rec *igProperty_GetRecordFolder(int, void *);
extern int DAT_005159f0[4];
extern int DAT_005159f8[4];
extern int DAT_00515aa8[4];
int FUN_003d0760(beNDMWPanelWaza *arg0, beNDMWPanelWazaInfoRam *arg1) {
    int len;
    int start;
    beNDMWPanelWazaInfoWork *s2;
    s2 = (beNDMWPanelWazaInfoWork *)arg1->_work;
    if (((beNDMWPanelObjectItem *)s2->_panelItem)->_isNoHealing != 0) {
        return 0;
    }
    beMessenger_SelectGroup(arg0->_messenger, &DAT_005159f0[0]);
    beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_005159f8[0]);
    int o = beMessenger_GetObject(arg0->_messenger, 0);
    igObjectList *arr = igProperty_GetRecordFolder(o, &DAT_00515aa8[0])->f12;
    int best = -1;
    int idx = 0;
    int n = arr->_count - 2;
    int j = 0;
    int t;
    beNDMWItemDisk *it;
    beNDMWItemDisk **p;
    if (j < n) {
        p = (beNDMWItemDisk **)arr->_data;
        do {
            it = *p;
            if (it->_kazu != 0) {
                t = it->_recNo;
                if ((t <= 2 || t == 9) && best < t) {
                    len = idx - 3;
                    best = t;
                    start = idx;
                    if (len < 0) {
                        len = 0;
                    } else {
                        start = idx - len;
                    }
                }
                idx += 1;
            }
            j += 1;
            p += 1;
        } while (j < n);
    }
    if (best != -1) {
        ((ItemPanelShim *)s2->_panelItem)->v21();
        ((beNDMWPanelObjectItem *)s2->_panelItem)->_cursor = start;
        ((beNDMWPanelObjectItem *)s2->_panelItem)->_offset = len;
        ((beNDMWPanelObjectItem *)s2->_panelItem)->_isEmg = 1;
        return 1;
    }
    return 0;
}
}
