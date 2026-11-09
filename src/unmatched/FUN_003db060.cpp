#include "dw4/reflected.h"
extern "C" {
int FUN_003614f0(...);
int beUnicodeObj_AllocateBuffer(...);
int FUN_003d9e10(...);
int FUN_003da7c0(...);
int beNDMWLoadIntf2ComMdlCtrl__StartAt(...);
int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
int FUN_003ec120(...);
int FUN_003ecad0(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int strcmp(...);
typedef struct Ent { int name; int val; int val2; } Ent;
extern Ent DAT_004cec70[16];
extern int *DAT_004cc830[4];
extern int DAT_00516cd0[4];
extern int DAT_00516cf8[4];
extern int DAT_00516db0[4];
extern int DAT_00516dc8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
#define SLOT_ROW(ci, pl) ((beNDMWLoadSavePlWork *)((int *)((beNDMWLoadSavePlWorkList *)(ci)->_flagWork)->_data)[pl])
#define SLOT_ITEMS(ci, pl) ((int *)((beNDMWDegiDataList *)((beNDMWLoadSlotPlayer *)SLOT_ROW(ci, pl)->_haveSaveData)->_saveDataList)->_data)
/* matching construct: the model controller's _pos is a vec3 but reflected.h truncates it to one int; a typed receiver here grows the function, so the float view stays local */
struct Ob { char p[28]; float v28; float v32; float v36; };
struct V3 { float x; float y; float z; };
/* Owning stack reference to the slot's name text; released on scope exit (reference count in the
 * low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" unsigned char FUN_003db060(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    int sp11C;
    beNDMWLoadCtrl2CommonIntf *sp100;
    int spF0;
    beNDMWLoadIntf2DegiStateCtrl *spE0;
    unsigned char spD0;
    int spC0;
    int spB0;
    int spA0;
    int al;
    unsigned short *a2;
    unsigned short *src;
    int n;
    unsigned short *v1;
    Ob *s0;
    int s2;
    sp11C = arg1;
    sp100 = (beNDMWLoadCtrl2CommonIntf *)arg0->_commonIntf;
    s0 = (Ob *)arg0->_comMdlCtrl;
    spD0 = 0;
    s2 = arg0->_textOrder;
    spF0 = arg0->_mesWin;
    spE0 = (beNDMWLoadIntf2DegiStateCtrl *)arg0->_statDisp;
    switch (sp11C) {
    default:
        spC0 = arg0->_st0;
        break;
    case 1:
        spC0 = arg0->_st1;
        break;
    case 2:
        spC0 = arg0->_st2;
        break;
    case 3:
        spC0 = arg0->_st3;
        break;
    }
    switch (spC0) {
    case 0: {
        Ent *s8;
        int s5;
        int s4;
        beNDMWDegiData *it;
        int **s2p;
        spB0 = 0;
        s2p = DAT_004cc830;
        spA0 = 0;
        do {
            it = (beNDMWDegiData *)SLOT_ITEMS(sp100, arg0->_plNo)[spB0];
            if (it->_isUse == 1) {
                if (*(char *)it->_dmkind != 0) {
                    s5 = 0;
                    s4 = 0;
                    s8 = DAT_004cec70;
                    V3 v1;
                loop_19:
                    if (strcmp(s8->name, it->_dmkind) == 0) {
                        s5 = s4;
                    } else {
                        s4 += 1;
                        s8 += 1;
                        if (s4 < 16) goto loop_19;
                    }
                    v1.x = s0->v28; v1.y = s0->v32; v1.z = s0->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt(s0, arg0->_plNo, *s2p, DAT_004cec70[s5].val, &v1, 1);
                } else {
                    V3 v2;
                    it->_isUse = 0;
                    v2.x = s0->v28; v2.y = s0->v32; v2.z = s0->v36;
                    beNDMWLoadIntf2ComMdlCtrl__StartAt(s0, arg0->_plNo, *s2p, DAT_00516cf8, &v2, 1);
                }
            } else {
                V3 v3;
                it->_isUse = 0;
                v3.x = s0->v28; v3.y = s0->v32; v3.z = s0->v36;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(s0, arg0->_plNo, *s2p, DAT_00516cf8, &v3, 1);
            }
            spA0 = spA0 + 4;
            spB0 = spB0 + 1;
            s2p++;
        } while (spB0 < 4);
        arg0->_isSaveArea = 1;
        {
            V3 v4;
            v4.x = s0->v28; v4.y = s0->v32; v4.z = s0->v36;
            beNDMWLoadIntf2ComMdlCtrl__StartAt(s0, arg0->_plNo, DAT_00516db0, DAT_00516cd0, &v4, 1);
        }
        arg0->_isSelCur = 1;
        if (arg0->_kind == 0) {
            unsigned char fl;
            int s3;
            beNDMWDegiData *it2;
            int s0b;
            it2 = (beNDMWDegiData *)SLOT_ITEMS(sp100, arg0->_plNo)[arg0->_svDataSelPoint];
            fl = 1;
            if (it2->_isUse == 1) {
                s3 = 0;
                s0b = 0;
            loop_31:
                {
                    beNDMWDegiData *o;
                    char *ca, *cb;
                    if (s3 != arg0->_plNo && (o = (beNDMWDegiData *)((int *)((beNDMWDegiDataList *)sp100->_gameUseData)->_data)[s3], o->_isUse == 1) && o->_id == it2->_id && (ca = (char *)o->_dmName, cb = (char *)it2->_dmName, ca != 0) && cb != 0 && strcmp(ca, cb) == 0) {
                        fl = 0;
                    } else {
                        s3 += 1;
                        s0b += 4;
                        if (s3 < 4) goto loop_31;
                    }
                }
            }
            if (fl == 1) {
                arg0->_mesKind = 0;
                FUN_003ecad0(spF0, (arg0->_plNo << 16) | 0x513);
            } else {
                arg0->_mesKind = 1;
                FUN_003ecad0(spF0, (arg0->_plNo << 16) | 0x515);
            }
            FUN_003d9e10(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0], 0, arg0->_svDataSelPoint);
        } else {
            arg0->_mesKind = 0;
            FUN_003ecad0(spF0, (arg0->_plNo << 16) | 0x503);
            FUN_003d9e10(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0], 1, arg0->_plNo);
        }
        arg0->_isUpStatWin = 1;
        spC0 = spC0 + 1;
        break;
    }
    case 1:
        if ((FUN_003da7c0(((int *)((beNDMWLoadIntf2DegiStateList *)spE0->_statDataList)->_data)[0]) & 0xFF) == 1 && (beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(s0) & 0xFF) == 1) {
            int s4;
            beNDMWDegiData *it;
            int s0c;
            s4 = 0;
            s0c = 0;
            do {
                it = (beNDMWDegiData *)SLOT_ITEMS(sp100, arg0->_plNo)[s4];
                if (it->_isUse == 1) {
                    al = igObject_GetAllocator(arg0);
                    al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    igSmartPointer<beUnicodeObj> text((beUnicodeObj *)FUN_003614f0(al));
                    beUnicodeObj_AllocateBuffer(text.p, 8);
                    src = (unsigned short *)it->_dmNameUni;
                    n = 0;
                    a2 = (unsigned short *)text.p->_buffer;
                    v1 = a2;
                    for (n = 0; n < 8; n++) {
                        *v1 = src[1];
                        if (*v1 == 0) break;
                        src++;
                        v1++;
                    }
                    for (; n < 8; n++) a2[n] = 0;
                    FUN_003ec120(s2, DAT_00516dc8, arg0->_plNo, s4, text.p, 1, 0);
                } else {
                    it->_isUse = 0;
                    beNDMWLoadIntf2TextOrder_PublishIdLines(s2, (arg0->_plNo << 16) | 0x300 | s4, 0);
                }
                s4 += 1;
                s0c += 4;
            } while (s4 < 4);
            spD0 = 1;
            spC0 = spC0 + 1;
        }
        break;
    case 2:
        spD0 = 1;
        break;
    }
    switch (sp11C) {
    default:
        arg0->_st0 = spC0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = spC0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = spC0;
        arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = spC0;
        break;
    }
    return spD0;
}
