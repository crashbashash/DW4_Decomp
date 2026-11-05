/* 0x003e3070 - beNDMWLoadIntf2SelSlot__RefreshSlotMarks (2832 bytes). beNDMWLoadIntf2SelSlot helper ("ss_select" in docs/engine/load-intf2.md):
 * per-frame refresh of the memory-card slot rows. For each mark row (2 when _mode == 0, else 5) it asks the
 * messenger target whether the row's message is registered, then registers (or updates) it while the row's
 * memory-card slot reports _isConnect (the row being selected, arg1, counts as not connected), and unregisters
 * it otherwise; finally it raises/clears the _mcStat "on" flag with a text-order notification.
 * Receiver, _commonIntf -> _mcUtilCtrl -> _slot -> _data[] -> _isConnect are reflected fields; the _comMdlCtrl target
 * (vec3 at +28) has no reflected class. Function and helper names are not recovered. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsRunning(struct Target *, int, char *);
int beNDMWLoadIntf2ComMdlCtrl__StartAt(struct Target *, int, char *, char *, struct Vec3 *, int);
int beNDMWLoadIntf2ComMdlCtrl__Play(struct Target *, int, char *, char *, int);
int beNDMWLoadIntf2ComMdlCtrl__Close(struct Target *, int, char *, char *, int);
int beNDMWLoadIntf2TextOrder_PublishIdLines(int, int, int);
int TextOrder_PublishLineListOnly(int, int);
typedef struct SlotEntry { int a; int idx; } SlotEntry;
extern SlotEntry DAT_004cd060[];
extern SlotEntry DAT_004cd090[];
extern char DAT_00516d30[];
extern char DAT_00517170[];
extern char DAT_00517180[];
extern char DAT_00517190[];
extern char DAT_005171a0[];
extern char DAT_005171b0[];
extern char DAT_005171c0[];
extern char DAT_005171d0[];
extern char DAT_005171e0[];
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Target { char p[28]; float x, y, z; } Target;
/* _commonIntf -> _mcUtilCtrl -> _slot is the memory-card slot list; _isConnect is the per-slot card-present flag. */
#define MC_SLOTS(owner) ((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)(owner)->_mcUtilCtrl)->_slot)
#define MC_SLOT(list, i) (((beNDMWMcSlot **)(list)->_data)[i])
/* _comMdlCtrl: its class is not reflected; the vec3 at +28 is all this function reads. */
#define TGT ((Target *)self->_comMdlCtrl)
void beNDMWLoadIntf2SelSlot__RefreshSlotMarks(beNDMWLoadIntf2SelSlot *self, int arg1) {
    beNDMWMcSlotList *r;
    beNDMWLoadCtrl2CommonIntf *owner = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    SlotEntry *base;
    switch (self->_kindHard) {
    default: {
    if (self->_mode == 0) {
        int i;
        SlotEntry *e;
        int h;
        base = DAT_004cd090;
        e = base;
        for (i = 0; i < 2; i++) {
            unsigned char st = MC_SLOT(MC_SLOTS(owner), e->idx)->_isConnect;
            if (arg1 == i) st = 0;
            if (st == 1) {
        switch (i) {
        case 0:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*2, DAT_00517170) == 0) {
                Vec3 va;
                Target *t = TGT; va.x = t->x; va.y = t->y; va.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(TGT, self->_ramNo*2, DAT_00517170, DAT_00517180, &va, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play(TGT, self->_ramNo*2, DAT_00517170, DAT_00517180, 0);
            }
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*2+1, DAT_00517170) == 0) {
                Vec3 vb;
                Target *t = TGT; vb.x = t->x; vb.y = t->y; vb.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(TGT, self->_ramNo*2+1, DAT_00517170, DAT_00517190, &vb, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play(TGT, self->_ramNo*2+1, DAT_00517170, DAT_00517190, 0);
            }
            break;
        }
            } else {
        switch (i) {
        case 0:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*2, DAT_00517170) == 1) beNDMWLoadIntf2ComMdlCtrl__Close(TGT, self->_ramNo*2, DAT_00517170, DAT_00516d30, 0);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*2+1, DAT_00517170) == 1) beNDMWLoadIntf2ComMdlCtrl__Close(TGT, self->_ramNo*2+1, DAT_00517170, DAT_00516d30, 0);
            break;
        }
            }
            e++;
        }
        h = self->_textOrder;
        if (self->_mcStat == 0) {
            r = MC_SLOTS(owner);
            if (MC_SLOT(r, base[self->_selPoint].idx)->_isConnect == 1) {
                self->_mcStat = 1;
                TextOrder_PublishLineListOnly(h, (self->_ramNo << 16) | 0x102e);
            }
        } else {
            r = MC_SLOTS(owner);
            if (MC_SLOT(r, base[self->_selPoint].idx)->_isConnect != 1) {
                self->_mcStat = 0;
                beNDMWLoadIntf2TextOrder_PublishIdLines(h, (self->_ramNo << 16) | 0x102e, 0);
            }
        }
    } else {
        int i;
        SlotEntry *e;
        int h;
        base = DAT_004cd060;
        e = base;
        for (i = 0; i < 5; i++) {
            unsigned char st = MC_SLOT(MC_SLOTS(owner), e->idx)->_isConnect;
            if (arg1 == i) st = 0;
            if (st == 1) {
        switch (i) {
        case 0:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*5, DAT_005171a0) == 0) {
                Vec3 va;
                Target *t = TGT; va.x = t->x; va.y = t->y; va.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(TGT, self->_ramNo*5, DAT_005171a0, DAT_005171b0, &va, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play(TGT, self->_ramNo*5, DAT_005171a0, DAT_005171b0, 0);
            }
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*5+1, DAT_005171a0) == 0) {
                Vec3 vb;
                Target *t = TGT; vb.x = t->x; vb.y = t->y; vb.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(TGT, self->_ramNo*5+1, DAT_005171a0, DAT_005171c0, &vb, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play(TGT, self->_ramNo*5+1, DAT_005171a0, DAT_005171c0, 0);
            }
            break;
        case 2:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*5+2, DAT_005171a0) == 0) {
                Vec3 vc;
                Target *t = TGT; vc.x = t->x; vc.y = t->y; vc.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(TGT, self->_ramNo*5+2, DAT_005171a0, DAT_005171d0, &vc, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play(TGT, self->_ramNo*5+2, DAT_005171a0, DAT_005171d0, 0);
            }
            break;
        case 3:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*5+3, DAT_005171a0) == 0) {
                Vec3 vd;
                Target *t = TGT; vd.x = t->x; vd.y = t->y; vd.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(TGT, self->_ramNo*5+3, DAT_005171a0, DAT_005171e0, &vd, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play(TGT, self->_ramNo*5+3, DAT_005171a0, DAT_005171e0, 0);
            }
            break;
        case 4:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*2, DAT_00517170) == 0) {
                Vec3 ve;
                Target *t = TGT; ve.x = t->x; ve.y = t->y; ve.z = t->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(TGT, self->_ramNo*2, DAT_00517170, DAT_00517190, &ve, 0);
            } else {
                beNDMWLoadIntf2ComMdlCtrl__Play(TGT, self->_ramNo*2, DAT_00517170, DAT_00517190, 0);
            }
            break;
        }
            } else {
        switch (i) {
        case 0:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*5, DAT_005171a0) == 1) beNDMWLoadIntf2ComMdlCtrl__Close(TGT, self->_ramNo*5, DAT_005171a0, DAT_00516d30, 0);
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*5+1, DAT_005171a0) == 1) beNDMWLoadIntf2ComMdlCtrl__Close(TGT, self->_ramNo*5+1, DAT_005171a0, DAT_00516d30, 0);
            break;
        case 2:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*5+2, DAT_005171a0) == 1) beNDMWLoadIntf2ComMdlCtrl__Close(TGT, self->_ramNo*5+2, DAT_005171a0, DAT_00516d30, 0);
            break;
        case 3:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*5+3, DAT_005171a0) == 1) beNDMWLoadIntf2ComMdlCtrl__Close(TGT, self->_ramNo*5+3, DAT_005171a0, DAT_00516d30, 0);
            break;
        case 4:
            if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(TGT, self->_ramNo*2, DAT_00517170) == 1) beNDMWLoadIntf2ComMdlCtrl__Close(TGT, self->_ramNo*2, DAT_00517170, DAT_00516d30, 0);
            break;
        }
            }
            e++;
        }
        h = self->_textOrder;
        if (self->_mcStat == 0) {
            r = MC_SLOTS(owner);
            if (MC_SLOT(r, base[self->_selPoint].idx)->_isConnect == 1) {
                self->_mcStat = 1;
                TextOrder_PublishLineListOnly(h, (self->_ramNo << 16) | 0x102e);
            }
        } else {
            r = MC_SLOTS(owner);
            if (MC_SLOT(r, base[self->_selPoint].idx)->_isConnect != 1) {
                self->_mcStat = 0;
                beNDMWLoadIntf2TextOrder_PublishIdLines(h, (self->_ramNo << 16) | 0x102e, 0);
            }
        }
    }
    break;
    }
    case 1: case 2: break;
    }
}
} /* extern "C" */
