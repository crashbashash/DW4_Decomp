#include "dw4/reflected.h"
extern "C" {
int beNDMWLoadIntf2ComMdlCtrl__StartAt(int, int, int *, int *, float *, int);
int beNDMWLoadIntf2ComMdlCtrl__Play(int, int, int *, int *, int);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(int);
int beNDMWLoadIntf2ComMdlCtrl__IsRunning(int, int, int *);
int beNDMWLoadIntf2TextOrder_PublishIdLines(int, int, int);
int TextOrder_PublishLineListOnly(int, int);
typedef struct TE { int *name; int mark; } TE; /* name: the label string passed to StartAt */
extern TE DAT_004cd060[5];
extern TE DAT_004cd090[2];
extern int DAT_00516cd0[4];
extern int DAT_00517118[4];
extern int DAT_00517128[4];
extern int DAT_00517138[4];
extern int DAT_00517150[4];
extern int DAT_00517160[4];
extern int DAT_00517170[4];
extern int DAT_00517180[4];
extern int DAT_00517190[4];
extern int DAT_005171a0[4];
extern int DAT_005171b0[4];
extern int DAT_005171c0[4];
extern int DAT_005171d0[4];
extern int DAT_005171e0[4];
typedef struct V3 { float x, y, z; } V3;
typedef struct Own { char p[28]; V3 pos; } Own;
typedef struct Mk { char p[8]; unsigned char made; } Mk;
typedef struct ML { char p[16]; Mk **arr; } ML;
typedef struct MQ { char p0[15]; unsigned char b15; char p1[28]; ML *list; } MQ;
typedef struct CI { char p[52]; MQ *q; } CI;

unsigned char beNDMWLoadIntf2SelSlot__Open(beNDMWLoadIntf2SelSlot *self, int mark) {
    float va[3], vb[3], vc[3], vd[3], ve[3], vf[3];
    float v0a[3], v0b[3], v0c[3], v0d[3], v0e[3], v0f[3];
    CI *ci;
    Own *o;
    TE *tb2;
    TE *tbl;
    int i;
    int j;
    ML *ml;
    int to;
    if (self->_st0 != 0) {
        return 0;
    }
    ci = (CI *)self->_commonIntf;
    switch (self->_kindHard) {
    case 1:
    case 2:
        break;
    default:
        /* kind 0 once ran an empty counted loop here; the dead loop survives as a CFG join so the _st1 dispatch rematerialises its compare constants */
        switch (self->_kindHard) {
        case 0:
            for (i = 0; i < 1; i++) {
            }
        }
        switch (self->_st1) {
        case 0:
            if (mark != -1) {
                self->_selPoint = mark;
            }
            if (ci->q->b15 == 0) {
                o = (Own *)self->_comMdlCtrl; va[0] = o->pos.x; va[1] = o->pos.y; va[2] = o->pos.z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo, DAT_00517118, DAT_00517128, va, 1);
                self->_mode = 0;
            } else {
                o = (Own *)self->_comMdlCtrl; vb[0] = o->pos.x; vb[1] = o->pos.y; vb[2] = o->pos.z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo, DAT_00517118, DAT_00517138, vb, 1);
                self->_mode = 1;
            }
            o = (Own *)self->_comMdlCtrl; vc[0] = o->pos.x; vc[1] = o->pos.y; vc[2] = o->pos.z;
            beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo, DAT_00517150, DAT_00516cd0, vc, 1);
            self->_isReOpenReq = 0;
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(self->_comMdlCtrl) & 0xFF) == 1) {
                if (self->_mode == 0) {
                    tbl = DAT_004cd090;
                    o = (Own *)self->_comMdlCtrl; vd[0] = o->pos.x; vd[1] = o->pos.y; vd[2] = o->pos.z;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo, DAT_00517160, tbl[self->_selPoint].name, vd, 1);
                    for (i = 0; i < 2; i++) {
                        if (ci->q->list->arr[tbl[i].mark]->made == 1) {
                            switch (i) {
                            case 0:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; ve[0] = o->pos.x; ve[1] = o->pos.y; ve[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517180, ve, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517180, 0);
                                }
                                break;
                            case 1:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; vf[0] = o->pos.x; vf[1] = o->pos.y; vf[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170, DAT_00517190, vf, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170, DAT_00517190, 0);
                                }
                                break;
                            }
                        }
                    }
                    to = self->_textOrder;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x100C, 0);
                    switch (self->_selPoint) {
                    case 0:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1100, 0);
                        break;
                    case 1:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1101, 0);
                        break;
                    }
                    ml = ci->q->list;
                    if (ml->arr[tbl[self->_selPoint].mark]->made != 1) {
                        self->_mcStat = 0;
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x102E, 0);
                    } else {
                        self->_mcStat = 1;
                        TextOrder_PublishLineListOnly(to, (self->_ramNo << 16) | 0x102E);
                    }
                    self->_st1 = self->_st1 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                } else {
                    tb2 = DAT_004cd060;
                    o = (Own *)self->_comMdlCtrl; v0a[0] = o->pos.x; v0a[1] = o->pos.y; v0a[2] = o->pos.z;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo, DAT_00517160, tb2[self->_selPoint].name, v0a, 1);
                    for (j = 0; j < 5; j++) {
                        if (ci->q->list->arr[tb2[j].mark]->made == 1) {
                            switch (j) {
                            case 0:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0b[0] = o->pos.x; v0b[1] = o->pos.y; v0b[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0, DAT_005171b0, v0b, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0, DAT_005171b0, 0);
                                }
                                break;
                            case 1:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0c[0] = o->pos.x; v0c[1] = o->pos.y; v0c[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0, DAT_005171c0, v0c, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0, DAT_005171c0, 0);
                                }
                                break;
                            case 2:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0d[0] = o->pos.x; v0d[1] = o->pos.y; v0d[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0, DAT_005171d0, v0d, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0, DAT_005171d0, 0);
                                }
                                break;
                            case 3:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0e[0] = o->pos.x; v0e[1] = o->pos.y; v0e[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0, DAT_005171e0, v0e, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0, DAT_005171e0, 0);
                                }
                                break;
                            case 4:
                                if (!(beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170) & 0xFF)) {
                                    o = (Own *)self->_comMdlCtrl; v0f[0] = o->pos.x; v0f[1] = o->pos.y; v0f[2] = o->pos.z;
                                    beNDMWLoadIntf2ComMdlCtrl__StartAt(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517190, v0f, 0);
                                } else {
                                    beNDMWLoadIntf2ComMdlCtrl__Play(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00517190, 0);
                                }
                                break;
                            }
                        }
                    }
                    to = self->_textOrder;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x100C, 0);
                    switch (self->_selPoint) {
                    case 0:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1102, 0);
                        break;
                    case 1:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1103, 0);
                        break;
                    case 2:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1104, 0);
                        break;
                    case 3:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1105, 0);
                        break;
                    case 4:
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x1101, 0);
                        break;
                    }
                    ml = ci->q->list;
                    if (ml->arr[tb2[self->_selPoint].mark]->made != 1) {
                        self->_mcStat = 0;
                        beNDMWLoadIntf2TextOrder_PublishIdLines(to, (self->_ramNo << 16) | 0x102E, 0);
                    } else {
                        self->_mcStat = 1;
                        TextOrder_PublishLineListOnly(to, (self->_ramNo << 16) | 0x102E);
                    }
                    self->_st1 = self->_st1 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            }
            break;
        case 2:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(self->_comMdlCtrl) & 0xFF) == 1) {
                self->_isOpen = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
            }
            break;
        }
        }
    return self->_isOpen;
}
}
