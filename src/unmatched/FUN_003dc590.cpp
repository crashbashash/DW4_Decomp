#include "dw4/igSmartPointer.h"
extern "C" {
int strcmp(...);
struct Ob { char p[28]; float x; float y; float z; };
struct Ent { int name; int val; int val2; };
int FUN_003d9e70(...);
int FUN_003da7c0(...);
int beNDMWLoadIntf2ComMdlCtrl__StartAt(...);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
int FUN_003ec120(...);
beUnicodeObj *FUN_003614f0(int);
int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(beNDMWLoadIntf2DataSelIntf *);
extern Ent DAT_004cec70[16];
extern int DAT_004cc830[4];
extern int DAT_00516cf8[4];
extern int DAT_00516dc8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
unsigned char FUN_003dc590(beNDMWLoadIntf2DataSelIntf *arg0, int arg1);
}

#define DEGI(bk, pl, i) \
    ((beNDMWDegiData *)((int *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork *)((int *)((beNDMWLoadSavePlWorkList *)(bk)->_flagWork)->_data)[pl])->_haveSaveData)->_saveDataList)->_data)[i])
unsigned char FUN_003dc590(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    beNDMWLoadCtrl2CommonIntf *bk = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    Ob *ob = (Ob *)arg0->_comMdlCtrl;
    int snd = arg0->_textOrder;
    beNDMWLoadIntf2DegiStateCtrl *nd = (beNDMWLoadIntf2DegiStateCtrl *)arg0->_statDisp;
    unsigned char r = 0;
    int v;
    switch (arg1) {
    default: v = arg0->_st0; break;
    case 1: v = arg0->_st1; break;
    case 2: v = arg0->_st2; break;
    case 3: v = arg0->_st3; break;
    }
    switch (v) {
    case 0:
        FUN_003d9e70(((int *)((beNDMWLoadIntf2DegiStateList *)nd->_statDataList)->_data)[1], 0);
        arg0->_isDownStatWin = 0;
        v++;
        break;
    case 1:
        if ((FUN_003da7c0(((int *)((beNDMWLoadIntf2DegiStateList *)nd->_statDataList)->_data)[1]) & 0xFF) == 1) v++;
        break;
    case 2: {
        int i;
        int off = 0;
        for (i = 0; i < 4; i++) {
            beNDMWDegiData *it = DEGI(bk, arg0->_plNo, i);
            if (it->_isUse == 1) {
                int j = 0;
                int k = 0;
                for (; k < 16; k++) {
                    if (strcmp(DAT_004cec70[k].name, it->_dmkind) == 0) { j = k; break; }
                }
                float v1[3];
                v1[0] = ob->x; v1[1] = ob->y; v1[2] = ob->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(ob, arg0->_plNo, DAT_004cc830[i], DAT_004cec70[j].val, v1, 1);
            } else {
                float v2[3];
                v2[0] = ob->x; v2[1] = ob->y; v2[2] = ob->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(ob, arg0->_plNo, DAT_004cc830[i], DAT_00516cf8, v2, 1);
            }
        }
        arg0->_isSaveArea = 1;
        v++;
        break;
    }
    case 3:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(ob) & 0xFF) == 1) {
            int i;
            for (i = 0; i < 4; i++) {
                beNDMWDegiData *it = DEGI(bk, arg0->_plNo, i);
                if (it->_isUse == 1) {
                    int a = igObject_GetAllocator(arg0);
                    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    igSmartPointer<beUnicodeObj> rp(FUN_003614f0(a));
                    beUnicodeObj_AllocateBuffer(rp.p, 8);
                    unsigned short *dst = (unsigned short *)rp.p->_buffer;
                    unsigned short *src = (unsigned short *)it->_dmNameUni;
                    int n;
                    for (n = 0; n < 8; n++) {
                        dst[n] = src[n + 1];
                        if (dst[n] == 0) break;
                    }
                    for (; n < 8; n++) dst[n] = 0;
                    FUN_003ec120(snd, DAT_00516dc8, arg0->_plNo, i, rp.p, 1, 0);
                } else {
                    beNDMWLoadIntf2TextOrder_PublishIdLines(snd, (arg0->_plNo << 16) | 0x300 | i, 0);
                }
            }
            v++;
        }
        break;
    case 4:
        r = 1;
        break;
    }
    switch (arg1) {
    default:
        arg0->_st0 = v; arg0->_st3 = 0; arg0->_st2 = 0; arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = v; arg0->_st3 = 0; arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = v; arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = v;
        break;
    }
    return r;
}
