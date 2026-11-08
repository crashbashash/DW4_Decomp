#include "dw4/reflected.h"
extern "C" {
int beNDMWLoadIntf2ComMdlCtrl__StartAt(...);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
int FUN_003d9e10(...);
int FUN_003da7c0(...);
int FUN_003614f0(...);
int beUnicodeObj_AllocateBuffer(...);
int FUN_003ec120(...);
int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
int igObject_GetAllocator(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int strcmp(...);
typedef struct Ent { int name; int val; int val2; } Ent;
extern Ent DAT_004cec70[16];
extern int DAT_004cc830[4];
extern int DAT_00516cf8[4];
extern int DAT_00516dc8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct V3 { float x, y, z; };
/* Owning stack reference to the area's text object; released on scope exit (reference count in the
 * low 23 bits of _refCount). */
class ObjectRef {
public:
    beUnicodeObj *p;
    ObjectRef(beUnicodeObj *o) : p(o) {}
    ~ObjectRef() { beUnicodeObj *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" unsigned char FUN_003dcc60(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    beNDMWLoadCtrl2CommonIntf *spF0;
    beNDMWLoadIntf2DegiStateCtrl *spE0;
    unsigned char r;
    beNDMWLoadIntf2ComMdlCtrl *s0;
    int s2;
    int mode;
    int i;
    beNDMWDegiData *it;
    int off;
    unsigned short *dst0;
    unsigned short *src;
    int n;
    unsigned short *dst;
    int al;
    int a0;
    spF0 = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    s0 = (beNDMWLoadIntf2ComMdlCtrl *)arg0->_comMdlCtrl;
    r = 0;
    s2 = arg0->_textOrder;
    spE0 = (beNDMWLoadIntf2DegiStateCtrl *)arg0->_statDisp;
    switch (arg1) {
    default: mode = arg0->_st0; break;
    case 1: mode = arg0->_st1; break;
    case 2: mode = arg0->_st2; break;
    case 3: mode = arg0->_st3; break;
    }
    switch (mode) {
    case 0: {
        beNDMWDegiData *it;
        int i;
        int s5;
        int s4;
        int *s3;
        int off;
        i = 0;
        off = 0;
        s3 = DAT_004cc830;
        do {
            it = *(beNDMWDegiData **)((char *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)spF0->_flagWork)->_data)[arg0->_plNo]->_haveSaveData)->_saveDataList)->_data + off);
            if (it->_isUse == 1) {
                V3 va;
                s5 = 0;
                for (s4 = 0; s4 < 16; s4++) {
                    if (strcmp(DAT_004cec70[s4].name, it->_dmkind) == 0) { s5 = s4; break; }
                }
                va.x = s0->_pos[0]; va.y = s0->_pos[1]; va.z = s0->_pos[2];
                beNDMWLoadIntf2ComMdlCtrl__StartAt(s0, arg0->_plNo, *s3, DAT_004cec70[s5].val, &va, 1);
            } else {
                V3 vb;
                vb.x = s0->_pos[0]; vb.y = s0->_pos[1]; vb.z = s0->_pos[2];
                beNDMWLoadIntf2ComMdlCtrl__StartAt(s0, arg0->_plNo, *s3, DAT_00516cf8, &vb, 1);
            }
            i += 1;
            off += 4;
            s3 += 1;
        } while (i < 4);
        arg0->_isSaveArea = 1;
        FUN_003d9e10(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0], 1, arg0->_plNo);
        arg0->_isUpStatWin = 1;
        mode += 1;
        break;
    }
    case 1:
        if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(s0) & 0xFF) == 1 && (FUN_003da7c0(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]) & 0xFF) == 1) {
            i = 0;
            off = 0;
            mode += 1;
            do {
                it = *(beNDMWDegiData **)((char *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)((beNDMWLoadSavePlWork **)((beNDMWLoadSavePlWorkList *)spF0->_flagWork)->_data)[arg0->_plNo]->_haveSaveData)->_saveDataList)->_data + off);
                if (it->_isUse == 1) {
                    al = igObject_GetAllocator(arg0, arg0->_plNo);
                    if (GPR_00554c14 != 0) a0 = al; else a0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    ObjectRef rcs((beUnicodeObj *)FUN_003614f0(a0));
                    beUnicodeObj_AllocateBuffer(rcs.p, 8);
                    src = (unsigned short *)it->_dmNameUni;
                    n = 0;
                    dst0 = (unsigned short *)rcs.p->_buffer;
                    dst = dst0;
                    for (n = 0; n < 8; n++) {
                        *dst = src[1];
                        if (*dst == 0) break;
                        src++;
                        dst++;
                    }
                    for (; n < 8; n++) dst0[n] = 0;
                    FUN_003ec120(s2, DAT_00516dc8, arg0->_plNo, i, rcs.p, 1, 0);
                } else {
                    beNDMWLoadIntf2TextOrder_PublishIdLines(s2, (arg0->_plNo << 0x10) | 0x300 | i, 0);
                }
                i += 1;
                off += 4;
            } while (i < 4);
        }
        break;
    case 2:
        r = 1;
        break;
    }
    switch (arg1) {
    default: arg0->_st0 = mode; arg0->_st3 = 0; arg0->_st2 = 0; arg0->_st1 = 0; break;
    case 1: arg0->_st1 = mode; arg0->_st3 = 0; arg0->_st2 = 0; break;
    case 2: arg0->_st2 = mode; arg0->_st3 = 0; break;
    case 3: arg0->_st3 = mode; break;
    }
    return r;
}
