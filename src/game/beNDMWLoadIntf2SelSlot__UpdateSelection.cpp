/* 0x003e1760 - beNDMWLoadIntf2SelSlot__UpdateSelection (4888 bytes): per-player option-menu cursor controller step.
 * Build: alternate (combat) compiler, "-O3,p -Iinclude".
 * Compiler-shape notes (each one measured):
 *  - the outer switch on the mode has "default:" laid out first with the body, "case 1: case 2: break;" last: that gives the
 *    retail compare order (2 then 1) and the unfilled delay slots;
 *  - the first button flag is an unsigned char temp (t = 1; if (...) t = 0) so the li becomes daddiu and the store gets andi;
 *  - the option-list pointer is its own local (ls) so the panel and list registers interfere as in retail;
 *  - the done paths jump to one common "return done" (goto out), the state switch (cases 0 to 2) has no default.
 */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beNDMWLoadIntf2ComMdlCtrl__IsRunning(int, int, int *);
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(int);
int beNDMWLoadIntf2ComMdlCtrl__StartAt(int, int, int *, int *, struct V3 *, int);
int beNDMWLoadIntf2ComMdlCtrl__Play(int, int, int *, int *, int);
int beNDMWLoadIntf2ComMdlCtrl__Close(int, int, int *, int *, int);
int beNDMWLoadIntf2TextOrder_PublishIdLines(int, int, int);
int TextOrder_PublishLineListOnly(int, int);
int FUN_003ee190(beNDMWLoadCtrl2CommonIntf *, int);
bePadData *bePadManager_GetPadForPlayer(int, int);
extern int DAT_00516d30[4];
extern int DAT_00516d50[4];
extern int DAT_00516e48[4];
extern int DAT_00517160[4];
extern int DAT_00517170[4];
extern int DAT_00517180[4];
extern int DAT_00517190[4];
extern int DAT_005171a0[4];
extern int DAT_005171b0[4];
extern int DAT_005171c0[4];
extern int DAT_005171d0[4];
extern int DAT_005171e0[4];
extern int DAT_005171f0[4];

struct OptEnt {
    int *w0; /* the label string passed to Play */
    int idx;
};
extern struct OptEnt DAT_004cd060[5];
extern struct OptEnt DAT_004cd090[2];
struct V3 {
    float x;
    float y;
    float z;
};

unsigned char beNDMWLoadIntf2SelSlot__UpdateSelection(beNDMWLoadIntf2SelSlot *self, unsigned char usePad, unsigned char checkDone) {
    beNDMWLoadCtrl2CommonIntf *owner;
    bePadData *pad;
    int held;
    int h1;
    int e;
    unsigned char t;
    unsigned char bU;
    unsigned char bD;
    unsigned char bL;
    unsigned char bR;
    struct OptEnt *tbl;
    int i;
    struct OptEnt *ent;
    beNDMWMcSlotList *ls;
    int wa;
    int wb;
    int wc;
    if (checkDone == 1) {
        if (self->_st0 != 1) {
            return 0;
        }
        if (self->_isSelect == 1) {
            return 1;
        }
    }
    owner = (beNDMWLoadCtrl2CommonIntf *)self->_commonIntf;
    held = 0;
    bU = 0;
    bD = 0;
    bL = 0;
    bR = 0;
    if (usePad == 1) {
        pad = bePadManager_GetPadForPlayer(self->_padManager, self->_ramNo);
        held = pad->_trigger;
        h1 = pad->_repeat;
        e = pad->_lTrg | pad->_lRpt;
        t = 1;
        if ((e & 1) == 0 && ((held | h1) & 0x10) == 0)
            t = 0;
        bU = t;
        bD = ((e & 4) != 0) || (((held | h1) & 0x40) != 0);
        bL = ((e & 8) != 0) || (((held | h1) & 0x80) != 0);
        bR = ((e & 2) != 0) || (((held | h1) & 0x20) != 0);
    }
    switch (self->_kindHard) {
    default: {
        if (self->_mode == 0) {
            tbl = DAT_004cd090;
            i = 0;
            ent = tbl;
            do {
                if (((beNDMWMcSlot **)((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot)->_data)[ent->idx]->_isConnect == 1) {
                    switch (i) {
                    case 0: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170) & 0xFF)) {
                            struct V3 v0;
                            beNDMWLoadIntf2ComMdlCtrl *m0 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v0.x = ((float *)&m0->_pos)[0];
                            v0.y = ((float *)&m0->_pos)[1];
                            v0.z = ((float *)&m0->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517180, &v0, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517180, 0);
                        }
                        break;
                    }
                    case 1: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170) & 0xFF)) {
                            struct V3 v1;
                            beNDMWLoadIntf2ComMdlCtrl *m1 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v1.x = ((float *)&m1->_pos)[0];
                            v1.y = ((float *)&m1->_pos)[1];
                            v1.z = ((float *)&m1->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170, DAT_00517190, &v1, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170, DAT_00517190, 0);
                        }
                        break;
                    }
                    }
                } else {
                    switch (i) {
                    case 0:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00516d30, 0);
                        }
                        break;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170, DAT_00516d30, 0);
                        }
                        break;
                    }
                }
                i++;
                ent++;
            } while (i < 2);
            wa = self->_textOrder;
            if (self->_mcStat == 0) {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                    self->_mcStat = 1;
                    TextOrder_PublishLineListOnly(wa, (self->_ramNo << 16) | 0x102E);
                }
            } else {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect != 1) {
                    self->_mcStat = 0;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(wa, (self->_ramNo << 16) | 0x102E, 0);
                }
            }
            if (((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_isMtap == 1) {
                self->_isReOpenReq = 1;
                self->_isSelect = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                goto out;
            }
        } else {
            tbl = DAT_004cd060;
            i = 0;
            ent = tbl;
            do {
                if (((beNDMWMcSlot **)((beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot)->_data)[ent->idx]->_isConnect == 1) {
                    switch (i) {
                    case 0: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0) & 0xFF)) {
                            struct V3 v0;
                            beNDMWLoadIntf2ComMdlCtrl *m0 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v0.x = ((float *)&m0->_pos)[0];
                            v0.y = ((float *)&m0->_pos)[1];
                            v0.z = ((float *)&m0->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0, DAT_005171b0, &v0, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0, DAT_005171b0, 0);
                        }
                        break;
                    }
                    case 1: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0) & 0xFF)) {
                            struct V3 v1;
                            beNDMWLoadIntf2ComMdlCtrl *m1 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v1.x = ((float *)&m1->_pos)[0];
                            v1.y = ((float *)&m1->_pos)[1];
                            v1.z = ((float *)&m1->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0, DAT_005171c0, &v1, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0, DAT_005171c0, 0);
                        }
                        break;
                    }
                    case 2: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0) & 0xFF)) {
                            struct V3 v2;
                            beNDMWLoadIntf2ComMdlCtrl *m2 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v2.x = ((float *)&m2->_pos)[0];
                            v2.y = ((float *)&m2->_pos)[1];
                            v2.z = ((float *)&m2->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0, DAT_005171d0, &v2, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0, DAT_005171d0, 0);
                        }
                        break;
                    }
                    case 3: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0) & 0xFF)) {
                            struct V3 v3;
                            beNDMWLoadIntf2ComMdlCtrl *m3 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v3.x = ((float *)&m3->_pos)[0];
                            v3.y = ((float *)&m3->_pos)[1];
                            v3.z = ((float *)&m3->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0, DAT_005171e0, &v3, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0, DAT_005171e0, 0);
                        }
                        break;
                    }
                    case 4: {
                        if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170) & 0xFF)) {
                            struct V3 v4;
                            beNDMWLoadIntf2ComMdlCtrl *m4 = (beNDMWLoadIntf2ComMdlCtrl *)self->_comMdlCtrl;
                            v4.x = ((float *)&m4->_pos)[0];
                            v4.y = ((float *)&m4->_pos)[1];
                            v4.z = ((float *)&m4->_pos)[2];
                            beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517190, &v4, 0);
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517190, 0);
                        }
                        break;
                    }
                    }
                } else {
                    switch (i) {
                    case 0:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0, DAT_00516d30, 0);
                        }
                        break;
                    case 1:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0, DAT_00516d30, 0);
                        }
                        break;
                    case 2:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0, DAT_00516d30, 0);
                        }
                        break;
                    case 3:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0, DAT_00516d30, 0);
                        }
                        break;
                    case 4:
                        if ((beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170) & 0xFF) == 1) {
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00516d30, 0);
                        }
                        break;
                    }
                }
                i++;
                ent++;
            } while (i < 5);
            if (((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_isMtap == 0) {
                self->_isReOpenReq = 1;
                self->_isSelect = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                goto out;
            }
            wa = self->_textOrder;
            if (self->_mcStat == 0) {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                    self->_mcStat = 1;
                    TextOrder_PublishLineListOnly(wa, (self->_ramNo << 16) | 0x102E);
                }
            } else {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect != 1) {
                    self->_mcStat = 0;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(wa, (self->_ramNo << 16) | 0x102E, 0);
                }
            }
        }
        switch (self->_st1) {
        case 0:
            if (self->_mode == 0) {
                if (bU) {
                    if (self->_selPoint != 0) {
                        self->_selPoint = 0;
                        beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                        self->_st1 = self->_st1 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                    }
                } else if (bD) {
                    if (self->_selPoint != 1) {
                        self->_selPoint = 1;
                        beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                        self->_st1 = self->_st1 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                    }
                } else if (held & 0x4000) {
                    ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                    if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                        FUN_003ee190(owner, self->_ramNo);
                        self->_mcSelPoint = tbl[self->_selPoint].idx;
                        beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_005171f0, 1);
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                    }
                } else if (held & 0x2000) {
                    self->_isCansel = 1;
                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516d50, 1);
                    self->_st1 = 2;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else if (held & 0x4000) {
                ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                    FUN_003ee190(owner, self->_ramNo);
                    self->_mcSelPoint = tbl[self->_selPoint].idx;
                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_005171f0, 1);
                    self->_st1 = 2;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else if (held & 0x2000) {
                self->_isCansel = 1;
                beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516d50, 1);
                self->_st1 = 2;
                self->_st3 = 0;
                self->_st2 = 0;
            } else if (bU) {
                if (self->_selPoint != 0) {
                    self->_selPoint = 0;
                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                    self->_st1 = self->_st1 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else if (bD) {
                int last = self->_selMax - 1;
                if (self->_selPoint != last) {
                    self->_selPoint = last;
                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                    self->_st1 = self->_st1 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else {
                if (self->_selPoint != self->_selMax - 1) {
                    if (bR) {
                        self->_selPoint = self->_selPoint + 1;
                        if (self->_selPoint >= self->_selMax - 1) {
                            self->_selPoint = self->_selMax - 2;
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                            self->_st1 = self->_st1 + 1;
                            self->_st3 = 0;
                            self->_st2 = 0;
                        }
                    } else if (bL) {
                        self->_selPoint = self->_selPoint - 1;
                        if (self->_selPoint < 0) {
                            self->_selPoint = 0;
                        } else {
                            beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516e48, 1);
                            self->_st1 = self->_st1 + 1;
                            self->_st3 = 0;
                            self->_st2 = 0;
                        }
                    }
                }
            }
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(self->_comMdlCtrl) == 1) {
                beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, tbl[self->_selPoint].w0, 0);
                wb = self->_textOrder;
                if (self->_mode == 0) {
                    switch (self->_selPoint) {
                    case 0:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1100, 0);
                        break;
                    case 1:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1101, 0);
                        break;
                    }
                } else {
                    switch (self->_selPoint) {
                    case 0:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1102, 0);
                        break;
                    case 1:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1103, 0);
                        break;
                    case 2:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1104, 0);
                        break;
                    case 3:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1105, 0);
                        break;
                    case 4:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wb, (self->_ramNo << 16) | 0x1101, 0);
                        break;
                    }
                }
                wc = self->_textOrder;
                if (self->_mcStat == 0) {
                    ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                    if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect == 1) {
                        self->_mcStat = 1;
                        TextOrder_PublishLineListOnly(wc, (self->_ramNo << 16) | 0x102E);
                    }
                } else {
                    ls = (beNDMWMcSlotList *)((beNDMWMcUtilCtrl *)owner->_mcUtilCtrl)->_slot;
                    if (((beNDMWMcSlot **)ls->_data)[tbl[self->_selPoint].idx]->_isConnect != 1) {
                        self->_mcStat = 0;
                        beNDMWLoadIntf2TextOrder_PublishIdLines(wc, (self->_ramNo << 16) | 0x102E, 0);
                    }
                }
                self->_st1 = 0;
                self->_st3 = 0;
                self->_st2 = 0;
            }
            break;
        case 2:
            if (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(self->_comMdlCtrl) == 1) {
                beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo, DAT_00517160, tbl[self->_selPoint].w0, 0);
                self->_isSelect = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
            }
            break;
        }
    }
    case 1:
    case 2:
        break;
    }
out:
    return self->_isSelect;
}
} /* extern "C" */
