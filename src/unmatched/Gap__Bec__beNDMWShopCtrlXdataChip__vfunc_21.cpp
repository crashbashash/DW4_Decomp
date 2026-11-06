#include "dw4/reflected.h"
extern "C" {
int sprintf(...);
long long FUN_00236f80(...);
int *FUN_002b90e0(...);
int *FUN_002caa70(...);
int FUN_002eb010(int);
int igObject_IsKindOf(...);
int *FUN_003b4d90(...);
int *FUN_003b4f50(...);
int *FUN_003b51b0(...);
int *FUN_003c87f0(...);
int FUN_003f5410(...);
int FUN_00448660(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringList_AppendRetained(int, int **);
int StringList_CopyRetained(...);
int StringPool_Construct(int);
int StringPool_Intern(int, int *);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int beNDMWItemBase_GetRecordInt(...);
int *beNDMWItemBase_GetRecordString(...);
int beNDMWShopCtrlXdataChip_RefreshText(...);
int beNDMWShopCtrlXdataChip_UpdatePageCount(...);
int beNDMWWindowSelect_CanRequestFO2TOP(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_RunMessageScript(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int *igProperty_GetRecord(...);
int *igProperty_GetRecordFolder(...);
extern int *DAT_004cf8a0[4];
extern int *DAT_004cf8a4[4];
extern int *DAT_004cf8a8[4];
extern int *DAT_004cf8ac[4];
extern int DAT_004cfaa0[8];
extern int DAT_0051b1c8[4];
extern int DAT_0051b220[4];
extern int DAT_0051b248[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3a0[4];
extern int DAT_0051b3b0[4];
extern int DAT_0051b3c8[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b3f8[4];
extern int DAT_0051b408[4];
extern int DAT_0051b418[4];
extern int DAT_0051b420[4];
extern int DAT_0051b440[4];
extern int DAT_0051b448[4];
extern int DAT_0051b460[4];
extern int DAT_0051b468[4];
extern int DAT_0051b470[4];
extern int DAT_0051b498[4];
extern int DAT_0051b4a0[4];
extern int DAT_0051b528[4];
extern int DAT_0051b548[4];
extern int DAT_0051b590[4];
extern int DAT_0051b598[4];
extern int DAT_0051b610[4];
extern int DAT_0051b620[4];
extern int DAT_0051b668[4];
extern int DAT_0051b678[4];
extern int DAT_0051b680[4];
extern int DAT_0051bd60[4];
extern int DAT_0051bd98[4];
extern int DAT_0051bdf0[4];
extern int DAT_0051be00[4];
extern int DAT_0051be10[4];
extern int DAT_0051be20[4];
extern int DAT_0051be38[4];
extern int DAT_0051be40[4];
extern int DAT_0051be50[4];
extern int DAT_0051be58[4];
extern int DAT_0051be68[4];
extern int DAT_0051be78[4];
extern int DAT_0051be88[4];
extern int DAT_0051be90[4];
extern int DAT_0051be98[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058abd8[4];
extern int DAT_0058b028[4];
extern unsigned char GPR_00554c14;
}

struct ChipVT {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void v22(int *, int *);
    virtual int v23();
    virtual int v24();
};
typedef struct ChipRecord {
    char p[12];
    int f12;
} ChipRecord;

struct ChipUtil { static inline bool IsChip(beNDMWItemBase *e) { if (e != 0) { return e->_kindNo == 3; } return false; } static inline int *CastSel(int *p) { if (p != 0 && igObject_IsKindOf(p, DAT_0058abd8[0]) != 0) return p; return 0; } };
/* matching construct: macro reproduces the inlined intern/append/release sequence */
#define INTERN_APPEND(slot, field, text) { \
    int *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (DAT_00586f20[0] == 0) { \
            int pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = (int *)StringPool_Intern(DAT_00586f20[0], (int *)(text)); \
    } \
    slot = tok; \
    StringList_AppendRetained(field, &slot); \
    { int *held = slot; \
    if (held != 0) { int *hd = held - 2; \
        int cnt = held[-1] - 1; held[-1] = cnt; \
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } } }

#define RELEASE(t) { \
    if ((t) != 0) { \
        (t)->_refCount = (t)->_refCount - 1; \
        if (((unsigned long long)((long long)(int)(t)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t); \
    } }

#define ALLOC(al) { \
    al = igObject_GetAllocator(arg0); \
    al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]); }

#define MSG3(group, sel) { \
    beMessenger_SelectGroup(arg0->_messenger, group); \
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo); \
    beMessenger_DispatchSelected(arg0->_messenger, sel); }

extern "C" void Gap__Bec__beNDMWShopCtrlXdataChip__vfunc_21(beNDMWShopCtrlXdataChip *arg0) {
    beNDMWStatusSelectE1 * volatile sp11C;
    beNDMWShopSelect00 * volatile sp118;
    beNDMWItemAbilityChip * volatile sp114;
    volatile int sp110;
    igIntList * volatile sp10C;
    beNDMWShopSelect01 * volatile sp108;
    beNDMWShopSelect00 * volatile sp104;
    beNDMWShopSelect00 * volatile sp100;
    int *spFC;
    int *spF8;
    int *spF4;
    int *spF0;
    int *spEC;
    int *spE8;
    int *spE4;
    int *spE0;
    int *spDC;
    int *spD8;
    int *spD4;
    int *spD0;
    int *spCC;
    int *spC8;
    int *spC4;
    int *spC0;
    int *spBC;
    int vecB[3];
    int vecA[3];
    char sp90[16];
    int sp70[8];
    int al;
    int i;
    int n;
    int **p;
    int *src;
    igObjectList *folder;
    igObjectList *list;
    igStringRefList *slist;
    beNDMWItemBase *item;
    ChipRecord *rec;
    int pages;
    int ret;
    int have;
    int s0;
    bool s1;
    long long s1i;
    int idx;
    int sel;
    int cost;
    int cur;
    int pocket;
    int *sub;
    int *first;
    int k;
    int li;
    int cst;
    int q;

    switch (arg0->_st0) {
    case 0:
        INTERN_APPEND(spFC, arg0->_textCloseTypeList, &DAT_0051b668[0])
        INTERN_APPEND(spF8, arg0->_textCloseNameList, &DAT_0051b1c8[0])
        INTERN_APPEND(spF4, arg0->_textCloseTypeList, &DAT_0051be10[0])
        INTERN_APPEND(spF0, arg0->_textCloseNameList, &DAT_0051b1c8[0])
        i = 0;
        p = &DAT_004cf8a0[0];
        do {
            FUN_003f5410(arg0, &DAT_0051b3c8[0], *p, &DAT_0051b590[0], &DAT_0051b598[0]);
            FUN_003f5410(arg0, &DAT_0051b680[0], *p, &DAT_0051b590[0], &DAT_0051b460[0]);
            i += 1;
            p += 1;
        } while (i < 12);
        FUN_003f5410(arg0, &DAT_0051b470[0], DAT_004cf8a0[0], &DAT_0051b590[0], &DAT_0051b598[0]);
        FUN_003f5410(arg0, &DAT_0051b470[0], &DAT_0051b548[0], &DAT_0051b590[0], &DAT_0051b598[0]);
        FUN_003f5410(arg0, &DAT_0051bd60[0], DAT_004cf8a0[0], &DAT_0051b590[0], &DAT_0051bd98[0]);
        FUN_003f5410(arg0, &DAT_0051bd60[0], DAT_004cf8a4[0], &DAT_0051b590[0], &DAT_0051bd98[0]);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            MSG3(&DAT_0051b398[0], &DAT_0051b3e8[0])
            rec = (ChipRecord *)igProperty_GetRecordFolder(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b528[0]);
            list = (igObjectList *)arg0->_itemBaseList;
            folder = (igObjectList *)rec->f12;
            n = list->_count;
            k = 0;
            if (0 < n) {
                do {
                    igObject *o = (igObject *)((int *)list->_data)[k];
                    RELEASE(o)
                    k += 1;
                } while (k < n);
            }
            { int m = list->_count; int j; for (j = 0; j < m; j++) ((int *)list->_data)[j] = 0; }
            list->_count = 0;
            for (q = 0; q < folder->_count; q++) {
                beNDMWItemBase *e = (beNDMWItemBase *)((int *)folder->_data)[q];
                if (e != 0) { int ok = e->_kindNo == 3; if (ok) ObjectList_AppendRetained(arg0->_itemBaseList, e); }
            }
            if (((igObjectList *)arg0->_itemBaseList)->_count <= 0) {
                arg0->_st1 = 0xA;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st3 = 0x491;
                return;
            }
            pages = beNDMWShopCtrlXdataChip_UpdatePageCount(arg0);
            if (arg0->_st2 == 0) {
                beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b610[0], 0, &DAT_0051be20[0], &DAT_0051b620[0]);
                beNDMWWindow_RunMessageScript(arg0, &DAT_0051b3b0[0], 0x456);
                vecA[0] = 0x436C0000;
                vecA[2] = 0;
                vecA[1] = 0x41C80000;
                vecB[0] = 0xC3120000;
                vecB[1] = 0x41C80000;
                vecB[2] = 0;
                ((ChipVT *)arg0)->v22(vecB, vecA);
            }
            ALLOC(al)
            sp11C = (beNDMWStatusSelectE1 *)FUN_003b51b0(al);
            beNDMWWindow_BindContext(sp11C, arg0, arg0->_insight, arg0->_playerNo, 0);
            ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp11C);
            {
                beNDMWStatusSelectE1 *t = sp11C;
                t->_offsetPos[0] = -121.0f;
                t->_offsetPos[1] = 128.0f;
                t->_offsetPos[2] = 0.0f;
            }
            sp11C->_selectMax = pages;
            sp11C->_startPoint = arg0->_cursor;
            {
                beNDMWStatusSelectE1 *t = sp11C;
                RELEASE(t)
            }
            arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            return;
        case 1:
            if (arg0->_retCode != -1) {
                beNDMWShopCtrlXdataChip_RefreshText(arg0, 1, 1);
            }
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
        case 2:
            sub = (int *)arg0->_subWindow;
            if (sub[2] == arg0->_nowProcKazu) {
                cur = arg0->_retCode;
                if (cur != -1) {
                    if (arg0->_st3 != cur) {
                        beNDMWShopCtrlXdataChip_RefreshText(arg0, 0, 1);
                        arg0->_st3 = arg0->_retCode;
                        return;
                    }
                    first = ChipUtil::CastSel((int *)*(int *)sub[4]);
                    if (first != 0 && beNDMWWindowSelect_CanRequestFO2TOP(first) != 0) {
                        s1 = false;
                        if (((ChipVT *)arg0)->v23() != 0) {
                            s1 = true;
                        } else if (((ChipVT *)arg0)->v24() != 0) {
                            s1 = true;
                        }
                        if (s1) {
                            ((beNDMWWindowSelect *)first)->_st0 = 4;
                            ((beNDMWWindowSelect *)first)->_st3 = 0;
                            ((beNDMWWindowSelect *)first)->_st2 = 0;
                            ((beNDMWWindowSelect *)first)->_st1 = 0;
                            arg0->_st1 = 1;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            first[21] = beNDMWShopCtrlXdataChip_UpdatePageCount(arg0);
                            return;
                        }
                    }
                }
            } else {
                cur = arg0->_retCode;
                switch (cur) {
                case -1:
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                default:
                    arg0->_cursor = cur;
                    arg0->_st1 = arg0->_st1 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
            }
            break;
        case 3:
            MSG3(&DAT_0051b398[0], &DAT_0051b3e8[0])
            have = ((ChipRecord *)igProperty_GetRecord(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b440[0]))->f12;
            pages = arg0->_nowPage;
            idx = arg0->_cursor + pages * 0xC;
            ret = beNDMWItemBase_GetRecordInt(((int *)((igObjectList *)arg0->_itemBaseList)->_data)[idx], FUN_00236f80(arg0->_insight, DAT_0058b028[0], pages), &DAT_0051be38[0]);
            if (ret == -1) {
                arg0->_st1 = 0xB;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st3 = 0x492;
                return;
            }
            if (have < ret) {
                arg0->_st1 = 0xB;
                arg0->_st3 = 0;
                arg0->_st2 = 0;
                arg0->_st3 = 0x489;
                return;
            }
            arg0->_st1 = arg0->_st1 + 1;
            arg0->_st3 = 0;
            arg0->_st2 = 0;
            return;
        case 4:
            switch (arg0->_st2) {
            case 0: {
                beNDMWItemBase *chip;
                long long status;
                int recNo;
                ALLOC(al)
                sp118 = (beNDMWShopSelect00 *)FUN_003b4f50(al);
                beNDMWWindow_BindContext(sp118, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp118);
                int pages0 = arg0->_nowPage;
                int idx0 = arg0->_cursor + pages0 * 0xC;
                status = FUN_00236f80(arg0->_insight, DAT_0058b028[0], pages0);
                chip = (beNDMWItemBase *)((int *)((igObjectList *)arg0->_itemBaseList)->_data)[idx0];
                recNo = chip->_recNo;
                if (chip->_isEquip != 0) {
                    chip->_recNo = recNo + 1;
                    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
                    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
                    MSG3(&DAT_0051b498[0], &DAT_0051bdf0[0])
                    chip->_recNo = recNo;
                    beMessenger_SelectReceivers(arg0->_messenger, &DAT_0051b398[0], 0, 0);
                    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3a0[0]);
                }
                ALLOC(al)
                sp114 = (beNDMWItemAbilityChip *)FUN_003c87f0(al);
                FUN_00448660(sp114, recNo + 1);
                FUN_003f5410(sp118, &DAT_0051b470[0], DAT_004cf8a0[0], beNDMWItemBase_GetRecordString(sp114, status, &DAT_0051b678[0]), &DAT_0051b598[0]);
                FUN_003f5410(sp118, &DAT_0051b448[0], DAT_004cf8a4[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                FUN_003f5410(sp118, &DAT_0051b448[0], DAT_004cf8a8[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                FUN_003f5410(sp118, &DAT_0051b448[0], DAT_004cf8ac[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                FUN_003f5410(sp118, &DAT_0051b470[0], DAT_004cf8a8[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                ALLOC(al)
                sp110 = (int)FUN_002b90e0(al);
                INTERN_APPEND(spEC, sp110, &DAT_0051b3f8[0])
                INTERN_APPEND(spE8, sp110, &DAT_0051b408[0])
                INTERN_APPEND(spE4, sp110, &DAT_0051b418[0])
                INTERN_APPEND(spE0, sp110, &DAT_0051b420[0])
                INTERN_APPEND(spDC, sp110, &DAT_0051be40[0])
                INTERN_APPEND(spD8, sp110, &DAT_0051be50[0])
                INTERN_APPEND(spD4, sp110, &DAT_0051be58[0])
                INTERN_APPEND(spD0, sp110, &DAT_0051be68[0])
                INTERN_APPEND(spCC, sp110, &DAT_0051be78[0])
                INTERN_APPEND(spC8, sp110, &DAT_0051be88[0])
                INTERN_APPEND(spC4, sp110, &DAT_0051be90[0])
                INTERN_APPEND(spC0, sp110, &DAT_0051be98[0])
                s1i = FUN_00236f80(arg0->_insight, DAT_0058b028[0]);
                ALLOC(al)
                {
                    igIntList *nw10 = (igIntList *)FUN_002caa70(al);
                    slist = (igStringRefList *)sp110;
                    sp10C = nw10;
                }
                li = 0;
                if (0 < slist->_count) {
                    do {
                        StringList_CopyRetained(&spBC, slist, li);
                        cst = beNDMWItemBase_GetRecordInt(sp114, s1i, spBC);
                        if (spBC != 0) {
                            int *hd = spBC - 2;
                            int c = spBC[-1] - 1;
                            spBC[-1] = c;
                            if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
                        }
                        if (cst > 0) {
                            sprintf(sp90, &DAT_0051b468[0], cst);
                            FUN_003f5410(sp118, &DAT_0051b448[0], &DAT_0051b220[0], sp90, &DAT_0051b460[0]);
                            if (li >= 8) li = 7;
                            {
                                struct Q2 { unsigned __int128 a[2]; }; *(Q2 *)sp70 = *(Q2 *)&DAT_004cfaa0[0];
                            }
                            sp118->_entCode = sp70[li];
                            break;
                        }
                        slist = (igStringRefList *)sp110;
                        li += 1;
                    } while (li < slist->_count);
                }
                {
                    igIntList *t = sp10C;
                    if (t != 0) {
                        t->_refCount = t->_refCount - 1;
                        igIntList *u = sp10C;
                        if (((unsigned long long)((long long)(int)u->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(u);
                    }
                }
                {
                    igStringRefList *t = (igStringRefList *)sp110;
                    RELEASE(t)
                }
                MSG3(&DAT_0051b398[0], &DAT_0051b3e8[0])
                s0 = ((ChipRecord *)igProperty_GetRecord(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b440[0]))->f12;
                sprintf(sp90, &DAT_0051b468[0], s0 - beNDMWItemBase_GetRecordInt(chip, status, &DAT_0051be38[0]));
                FUN_003f5410(sp118, &DAT_0051b448[0], &DAT_0051b248[0], sp90, &DAT_0051b460[0]);
                {
                    beNDMWItemAbilityChip *t = sp114;
                    RELEASE(t)
                }
                {
                    beNDMWShopSelect00 *t = sp118;
                    RELEASE(t)
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            }
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    ALLOC(al)
                    sp108 = (beNDMWShopSelect01 *)FUN_003b4d90(al);
                    beNDMWWindow_BindContext(sp108, arg0, arg0->_insight, arg0->_playerNo, 0x493);
                    ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp108);
                    {
                        beNDMWShopSelect01 *t = sp108;
                        RELEASE(t)
                    }
                    arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                    arg0->_st2 = arg0->_st2 + 1;
                    arg0->_st3 = 0;
                case 2:
                    if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                        MSG3(&DAT_0051b498[0], &DAT_0051be00[0])
                        switch (arg0->_retCode) {
                        case 0: {
                            beNDMWItemBase *chip2;
                            long long st2;
                            int cost2;
                            int sel2;
                            int cur2;
                            int pages2 = arg0->_nowPage;
                            int idx2 = arg0->_cursor + pages2 * 0xC;
                            st2 = FUN_00236f80(arg0->_insight, DAT_0058b028[0], pages2);
                            chip2 = (beNDMWItemBase *)((int *)((igObjectList *)arg0->_itemBaseList)->_data)[idx2];
                            MSG3(&DAT_0051b398[0], &DAT_0051b3e8[0])
                            sel2 = beMessenger_GetObject(arg0->_messenger, 0);
                            cur2 = ((ChipRecord *)igProperty_GetRecord(sel2, &DAT_0051b440[0]))->f12;
                            cost2 = beNDMWItemBase_GetRecordInt(chip2, st2, &DAT_0051be38[0]);
                            ChipRecord *r2 = (ChipRecord *)igProperty_GetRecord(sel2, &DAT_0051b440[0]);
                            r2->f12 = cur2 - cost2;
                            chip2->_recNo = chip2->_recNo + 1;
                            MSG3(&DAT_0051b398[0], &DAT_0051b3a0[0])
                            MSG3(&DAT_0051b498[0], &DAT_0051b4a0[0])
                            break;
                        }
                        default:
                            break;
                        }
                        arg0->_st1 = 0;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st2 = 1;
                        arg0->_st3 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 10:
            switch (arg0->_st2) {
            case 0:
                ALLOC(al)
                sp104 = (beNDMWShopSelect00 *)FUN_003b4f50(al);
                beNDMWWindow_BindContext(sp104, arg0, arg0->_insight, arg0->_playerNo, arg0->_st3);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp104);
                beNDMWShopSelect00 *w = sp104;
                if (DAT_00586f20[0] == 0) {
                    int pool = FUN_002eb010(0x10);
                    if (pool != 0) pool = StringPool_Construct(pool);
                    DAT_00586f20[0] = pool;
                }
                {
                    int *nw = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0051b548[0]);
                    int *old = (int *)w->_panelName;
                    if (old != 0) {
                        int *hd = old - 2;
                        int c = old[-1] - 1;
                        old[-1] = c;
                        if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
                    }
                    w->_panelName = (int)nw;
                }
                {
                    beNDMWShopSelect00 *t = sp104;
                    RELEASE(t)
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 11:
            switch (arg0->_st2) {
            case 0:
                ALLOC(al)
                sp100 = (beNDMWShopSelect00 *)FUN_003b4f50(al);
                beNDMWWindow_BindContext(sp100, arg0, arg0->_insight, arg0->_playerNo, arg0->_st3);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp100);
                {
                    beNDMWShopSelect00 *t = sp100;
                    RELEASE(t)
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)(arg0->_subWindow))->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)(arg0->_subWindow))->_count != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st2 = 1;
                    arg0->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}
