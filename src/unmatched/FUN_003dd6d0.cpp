/* Arena handles are 4-byte ints and are cast to pointers where followed. */
#include "dw4/igSmartPointer.h"
extern "C" {
struct Tab { int name; int f4; int *f8; };
int strcmp(int, int);
beUnicodeObj *FUN_003614f0(int);
int beUnicodeObj_AllocateBuffer(beUnicodeObj *, int);
int beNDMWLoadIntf2ComMdlCtrl__Play(int, int, int, int *, int);
int beNDMWLoadIntf2TextOrder_PublishIdLines(int, int, int);
int FUN_003ec120(int, int *, int, int, beUnicodeObj *, int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(beNDMWLoadIntf2DataSelIntf *);
extern int DAT_004cc830[4];
extern Tab DAT_004cec70[16];
extern int DAT_00516cf8[4];
extern int DAT_00516dc8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the area's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

extern "C" int FUN_003dd6d0(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    beNDMWLoadCtrl2CommonIntf *ctx = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    int s4 = arg0->_comMdlCtrl;
    int s8 = arg0->_textOrder;
    int sel;
    switch (arg1) {
    default:
        sel = arg0->_st0;
        break;
    case 1:
        sel = arg0->_st1;
        break;
    case 2:
        sel = arg0->_st2;
        break;
    case 3:
        sel = arg0->_st3;
        break;
    }
    int i;
    igIntList *lst = (igIntList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)ctx->_flagWork)->_data)[arg0->_plNo]->_haveSaveData)->_accessPlList;
    for (i = 0; i < lst->_count; i++) {
        {
            int s3 = ((int *)lst->_data)[i];
            int j = 0;
            do {
                beNDMWDegiData *e = ((beNDMWDegiData **)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)ctx->_flagWork)->_data)[s3]->_haveSaveData)->_saveDataList)->_data)[j];
                if (e->_isUse == 1) {
                    int k = 0;
                    int m;
                    for (m = 0; m < 16; m++) {
                        if (strcmp(DAT_004cec70[m].name, e->_dmkind) == 0) { k = m; break; }
                    }
                    beNDMWLoadIntf2ComMdlCtrl__Play(s4, s3, DAT_004cc830[j], DAT_004cec70[k].f8, 0);
                    int a = igObject_GetAllocator(arg0);
                    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    igSmartPointer<beUnicodeObj> r(FUN_003614f0(a));
                    beUnicodeObj_AllocateBuffer(r.p, 8);
                    unsigned short *base;
                    unsigned short *src;
                    unsigned short *dp;
                    int n;
                    src = (unsigned short *)e->_dmNameUni;
                    base = (unsigned short *)r.p->_buffer;
                    n = 0;
                    dp = base;
                    for (n = 0; n < 8; n++) {
                        *dp = src[1];
                        if (*dp == 0) break;
                        src++;
                        dp++;
                    }
                    for (; n < 8; n++) base[n] = 0;
                    FUN_003ec120(s8, DAT_00516dc8, s3, j, r.p, 1, 0);
                } else {
                    beNDMWLoadIntf2ComMdlCtrl__Play(s4, s3, DAT_004cc830[j], DAT_00516cf8, 0);
                    beNDMWLoadIntf2TextOrder_PublishIdLines(s8, (s3 << 16) | 0x300 | j, 0);
                }
                j++;
            } while (j < 4);
        }
    }
    switch (arg1) {
    default:
        arg0->_st0 = sel;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = sel;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = sel;
        arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = sel;
        break;
    }
    return 1;
}
