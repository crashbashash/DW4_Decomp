#include "dw4/reflected.h"
/* Receiver: beNDMWLoadIntf2DataSelIntf; host is its _commonIntf. _flagWork holds the per-player beNDMWLoadSavePlWork records
 * (_isCtrl, _haveSaveData, a beNDMWLoadSlotPlayer whose _saveDataList holds the four save areas); _gameUseData is a
 * beNDMWDegiDataList of the per-player Digimon records. The class behind _statDisp is not reflected. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
#define PLW(common, i) (((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)(common)->_flagWork)->_data)[i])
#define DEGI(common, i) (((beNDMWDegiData **)((beNDMWDegiDataList *)(common)->_gameUseData)->_data)[i])
#define AREAS(common, pl) (((beNDMWDegiData **)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)PLW(common, pl)->_haveSaveData)->_saveDataList)->_data))
typedef struct Node { int f0; char p0[12]; struct Node *n16; } Node;
extern int DAT_00516db0[4], DAT_00516e48[4], DAT_00516d50[4];
extern void *DAT_004cc840[4], *DAT_004cc850[4];
extern void *DAT_00586f20[4];
bePadData *bePadManager_GetPadForPlayer(int, int);
int FUN_003d9e40(int, int, int);
int FUN_003da7c0(int);
int beNDMWLoadIntf2ComMdlCtrl__Play(int, int, void *, void *, int);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(int);
int beNDMWLoadIntf2ComMdlCtrl__Close(int, int, void *, void *, int);
int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(int);
int FUN_003ee190(beNDMWLoadCtrl2CommonIntf *, int);
int FUN_003ecad0(int, int);
int FUN_002eb010(int);
void *StringPool_Construct(void *);
char *StringPool_Intern(void *, char *);
void StringChunk_ReleaseHeader(int, int *);
int igStrCmp(char *, char *);
unsigned char beNDMWLoadIntf2DataSelIntf__UpdateSelection(beNDMWLoadIntf2DataSelIntf *c, int sel) {
    unsigned char uniq;
    beNDMWLoadCtrl2CommonIntf *host = (beNDMWLoadCtrl2CommonIntf *)c->_commonIntf;
    int bits;
    beNDMWDegiData *s4;
    int up;
    int a = c->_comMdlCtrl;
    unsigned char dn;
    int i;
    int v;
    unsigned char rt;
    int h40 = c->_mesWin;
    unsigned char lf;
    unsigned char r = 0;
        Node *n = (Node *)c->_statDisp;
    switch (sel) {
    default: v = c->_st0; break;
    case 1: v = c->_st1; break;
    case 2: v = c->_st2; break;
    case 3: v = c->_st3; break;
    }
    bits = 0;
    up = 0;
    dn = 0;
    rt = 0;
    lf = 0;
    if (PLW(host, c->_plNo)->_isCtrl == 1) {
            unsigned char u;
        bePadData *p = bePadManager_GetPadForPlayer(c->_padManager, c->_plNo);
        int m;
        int y;
        bits = p->_trigger;
        y = p->_repeat;
        m = p->_lTrg | p->_lRpt;
        u = 1;
        if ((m & 1) || ((bits | y) & 0x10)) {} else u = 0;
        up = u;
        dn = (m & 4) || ((bits | y) & 0x40);
        rt = (m & 8) || ((bits | y) & 0x80);
        lf = (m & 2) || ((bits | y) & 0x20);
    }
    switch (v) {
    case 0: {
        int nw;
        int cur;
        cur = c->_svDataSelPoint;
        nw = cur;
        if (up) {
            if (cur == 2) nw = 0; else if (cur == 3) nw = 1;
        } else if (dn) {
            if (cur == 0) nw = 2; else if (cur == 1) nw = 3;
        } else if (lf) {
            if (cur == 0) nw = 1; else if (cur == 2) nw = 3;
        } else if (rt) {
            if (cur == 1) nw = 0; else if (cur == 3) nw = 2;
        }
        if (nw != cur) {
            c->_svDataSelPoint = nw;
            if (c->_kind == 0) FUN_003d9e40(n->n16->n16->f0, 0, c->_svDataSelPoint);
            beNDMWLoadIntf2ComMdlCtrl__Play(a, c->_plNo, DAT_00516db0, DAT_00516e48, 0);
            v = 1;
        } else if (bits & 0x4000) {
            if (c->_kind == 0) {
                s4 = AREAS(host, c->_plNo)[cur];
                if (s4->_isUse == 1) {
                    uniq = 1;
                    for (i = 0; i < 4; i++) {
                        char *y;
                        char *x;
                        beNDMWDegiData *o;
                        if (i == c->_plNo) continue;
                        o = DEGI(host, i);
                        if (o->_isUse != 1) continue;
                        if (o->_id != s4->_id) continue;
                        x = (char *)o->_dmName;
                        y = (char *)s4->_dmName;
                        if (x == 0 || y == 0) continue;
                        if (igStrCmp(x, y) == 0) { uniq = 0; break; }
                    }
                    if (uniq == 1) {
                        beNDMWDegiData *d;
                        char *old;
                        char *nw2;
                        char *src;
                        DEGI(host, c->_plNo)->_isUse = 1;
                        DEGI(host, c->_plNo)->_id = s4->_id;
                        d = DEGI(host, c->_plNo);
                        src = (char *)s4->_dmName;
                        if (DAT_00586f20[0] == 0) {
                            void *q = (void *)FUN_002eb010(16);
                            if (q != 0) q = StringPool_Construct(q);
                            DAT_00586f20[0] = q;
                        }
                        nw2 = StringPool_Intern(DAT_00586f20[0], src);
                        old = (char *)d->_dmName;
                        if (old != 0) {
                            int *hd = (int *)old - 2;
                            int rc = ((int *)old)[-1] - 1;
                            ((int *)old)[-1] = rc;
                            if (rc == 0) StringChunk_ReleaseHeader(*hd, hd);
                        }
                        d->_dmName = (int)nw2;
                        c->_isCancel = 0;
                        v = 2;
                    }
                }
            } else {
                FUN_003ee190(host, c->_plNo);
                c->_isCancel = 0;
                v = 2;
            }
        } else if (bits & 0x2000) {
            v = 4;
            c->_isCancel = 1;
        }
        if (c->_kind == 0) {
        unsigned char uniq2;
        int i2;
        beNDMWDegiData *s42;
            FUN_003d9e40(n->n16->n16->f0, 0, c->_svDataSelPoint);
            s42 = AREAS(host, c->_plNo)[c->_svDataSelPoint];
            if (s42->_isUse == 1) {
                uniq2 = 1;
                for (i2 = 0; i2 < 4; i2++) {
                    beNDMWDegiData *o;
                    char *x;
                    char *y;
                    if (i2 == c->_plNo) continue;
                    o = DEGI(host, i2);
                    if (o->_isUse != 1) continue;
                    if (o->_id != s42->_id) continue;
                    x = (char *)o->_dmName;
                    y = (char *)s42->_dmName;
                    if (x == 0 || y == 0) continue;
                    if (igStrCmp(x, y) == 0) { uniq2 = 0; break; }
                }
                if (uniq2 == 1) {
                    if (c->_mesKind != 0) { c->_mesKind = 0; FUN_003ecad0(h40, (c->_plNo << 16) | 0x513); }
                } else if (c->_mesKind != 1) {
                    c->_mesKind = 1; FUN_003ecad0(h40, (c->_plNo << 16) | 0x515);
                }
            } else if (c->_mesKind != 0) {
                c->_mesKind = 0; FUN_003ecad0(h40, (c->_plNo << 16) | 0x513);
            }
        }
        break;
    }
    case 1:
        if (c->_kind == 0) {
            if ((FUN_003da7c0(n->n16->n16->f0) & 0xFF) != 1) break;
        }
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(a) & 0xFF) == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Play(a, c->_plNo, DAT_00516db0, DAT_004cc840[c->_svDataSelPoint], 0);
            v = 0;
        }
        break;
    case 2:
        beNDMWLoadIntf2ComMdlCtrl__Close(a, c->_plNo, DAT_00516db0, DAT_004cc850[c->_svDataSelPoint], 1);
        c->_isSelCur = 0;
        v = 3;
        break;
    case 3:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(a) & 0xFF) == 1) v = 6;
        break;
    case 4:
        beNDMWLoadIntf2ComMdlCtrl__Close(a, c->_plNo, DAT_00516db0, DAT_00516d50, 1);
        c->_isSelCur = 0;
        v = 5;
        break;
    case 5:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(a) & 0xFF) == 1) v = 6;
        break;
    case 6:
        r = 1;
        break;
    }
    switch (sel) {
    default: c->_st0 = v; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; break;
    case 1: c->_st1 = v; c->_st3 = 0; c->_st2 = 0; break;
    case 2: c->_st2 = v; c->_st3 = 0; break;
    case 3: c->_st3 = v; break;
    }
    return r;
}
} /* extern "C" */
