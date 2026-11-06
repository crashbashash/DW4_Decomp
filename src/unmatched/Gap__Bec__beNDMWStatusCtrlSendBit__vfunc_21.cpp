/* State-machine update of the send-bit status window.
 * Matching construct: the first dispatch on the player-number list count is
 * 'switch (t) { case 1: default: ...; case 2: ...; case 3: ... }'; the double label makes the
 * default arm a join point. */
#include "dw4/reflected.h"
#pragma inline_depth(8)
extern "C" {
int sprintf(...);
int FUN_002eb010(...);
int FUN_003b45d0(...);
int FUN_003b4f50(...);
int FUN_003b51b0(...);
int FUN_003f5410(...);
int FUN_004402e0(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringList_AppendRetained(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendObject(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendNamed(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_PresentModel(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_RunMessageScript(...);
int bePadManager_GetPadForPlayer(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int igProperty_GetRecord(...);
int igProperty_GetRecordFolder(...);
typedef struct { int v[3]; } Tri;
extern Tri DAT_004cf740[4];
extern Tri DAT_004cf750[4];
extern int DAT_005199e0[4];
extern int DAT_005199e8[4];
extern int DAT_00519a58[4];
extern int DAT_00519a90[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519b50[4];
extern int DAT_00519b60[4];
extern int DAT_00519b68[4];
extern int DAT_00519b78[4];
extern int DAT_00519b90[4];
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_00519c10[4];
extern int DAT_00519c28[4];
extern int DAT_00519c50[4];
extern int DAT_00519cc8[4];
extern int DAT_00519cd8[4];
extern int DAT_00519ce8[4];
extern int DAT_00519d88[4];
extern int DAT_00519d98[4];
extern int DAT_00519f30[4];
extern int DAT_0051a060[4];
extern int DAT_0051a080[4];
extern int DAT_0051a180[4];
extern int DAT_0051a1d8[4];
extern int DAT_0051a1e8[4];
extern int DAT_0051a1f8[4];
extern int DAT_0051a210[4];
extern int DAT_0051a278[4];
extern int DAT_0051a288[4];
extern int DAT_0051a298[4];
extern int DAT_0051a2a8[4];
extern int DAT_0051a2b8[4];
extern int DAT_0051a2c8[4];
extern int DAT_0051a2d0[4];
extern int DAT_0051a2d8[4];
extern int DAT_0051a2e8[4];
extern int DAT_0051a2f0[4];
extern int DAT_0051a300[4];
extern int DAT_0051a310[4];
extern int DAT_0051a320[4];
extern int DAT_0051a328[4];
extern int DAT_0051a338[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
typedef igObject RefObj;
/* One releasing holder class per destructor copy. */
struct Ref {
    RefObj *p;
    Ref(void *x) { p = (RefObj *)x; }
    ~Ref() {
        RefObj *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct RefX {
    RefObj *p;
    RefX(void *x) { p = (RefObj *)x; }
    ~RefX() {
        RefObj *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct RefB {
    RefObj *p;
    RefB(void *x) { p = (RefObj *)x; }
    ~RefB() {
        RefObj *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct RefA {
    RefObj *p;
    RefA(void *x) { p = (RefObj *)x; }
    ~RefA() {
        RefObj *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
/* Interned-string reference (count at p[-1], header at p[-2]). */
struct StringRef {
    void *p;
    StringRef(void *x) { p = x; }
    ~StringRef() {
        if (p != 0) {
            int *header = (int *)((char *)p - 8);
            int count = *(int *)((char *)p - 4) - 1;
            *(int *)((char *)p - 4) = count;
            if (count == 0) StringChunk_ReleaseHeader(*header, header);
        }
    }
};

#define SEL(d) beMessenger_SelectGroup(p->_messenger, d)
#define APS(d) beMessenger_AppendString(p->_messenger, d)
#define API(d) beMessenger_AppendInt(p->_messenger, d)
#define APO(d) beMessenger_AppendObject(p->_messenger, d)
#define DSP(d) beMessenger_DispatchSelected(p->_messenger, d)

/* matching construct: allocator selection inlined as in retail (object allocator when the global flag is set, else selector 0x587110) */
struct H {
static inline int AllocFor(beNDMWStatusCtrlSendBit *q) {
    int base = igObject_GetAllocator(q);
    int al;
    if (GPR_00554c14 != 0) { al = base; } else { al = Memory_GetAllocatorBySelector(DAT_00587110[0]); }
    return al;
}

static inline void AddTextType(beNDMWStatusCtrlSendBit *q, const char *s) {
    void *v;
    int t;
    if (s == 0) { v = (void *)0; } else { if (DAT_00586f20[0] == 0) { t = FUN_002eb010(0x10); if (t != 0) { t = StringPool_Construct(t); } DAT_00586f20[0] = t; } v = StringPool_Intern(DAT_00586f20[0], s); }
    StringRef sv(v);
    StringList_AppendRetained(q->_textCloseTypeList, &sv.p);
}

static inline void AddTextName(beNDMWStatusCtrlSendBit *q, const char *s) {
    void *v;
    int t;
    if (s == 0) { v = (void *)0; } else { if (DAT_00586f20[0] == 0) { t = FUN_002eb010(0x10); if (t != 0) { t = StringPool_Construct(t); } DAT_00586f20[0] = t; } v = StringPool_Intern(DAT_00586f20[0], s); }
    StringRef sv(v);
    StringList_AppendRetained(q->_textCloseNameList, &sv.p);
}

};

extern "C" void Gap__Bec__beNDMWStatusCtrlSendBit__vfunc_21(beNDMWStatusCtrlSendBit *p) {
    Tri spF0;
    Tri spE0;
    int spD0[3], spC0[3], spB0[3];
    int spA0[4], sp90[4], sp80[4], sp70[4], sp60[4];
    int k, i, n, cnt;
    int *tbl;
    int k2, n2, oe;
    int o, al, rec, t, mx, b, sw;
    int pad, c0, c1, c3, c2, dig, e;
    bool up, dn;
    int i2; 

    switch (p->_st0) {
    case 0:
        t = ((igIntList *)p->_playerNoList)->_count;
        switch (t) { case 1: default: beNDMWWindow_PresentModelAtOrigin(p, DAT_0051a180, 0, DAT_0051a278, DAT_00519a58); break; case 2: beNDMWWindow_PresentModelAtOrigin(p, DAT_0051a180, 0, DAT_0051a288, DAT_00519a58); break; case 3: beNDMWWindow_PresentModelAtOrigin(p, DAT_0051a180, 0, DAT_0051a298, DAT_00519a58); break; }
        H::AddTextType(p, (const char *)DAT_0051a1d8);
        H::AddTextName(p, (const char *)DAT_005199e0);
        H::AddTextType(p, (const char *)DAT_0051a1d8);
        H::AddTextName(p, (const char *)DAT_005199e8);
        beNDMWWindow_RunMessageScript(p, DAT_00519b90, 0x4C);
        FUN_003f5410(p, DAT_0051a2a8, DAT_005199e0, DAT_00519b60, DAT_0051a1f8);
        FUN_003f5410(p, DAT_0051a2b8, DAT_005199e0, DAT_00519b60, DAT_0051a080);
        tbl = spF0.v;
        spF0 = DAT_004cf740[0];
        k = 0;
        if (0 < ((igIntList *)p->_playerNoList)->_count) {
            i = 0;
            do {
                n = *(int *)(((igIntList *)p->_playerNoList)->_data + i);
                SEL(DAT_00519ba0);
                API(n);
                DSP(DAT_00519ba8);
                n = beMessenger_GetObject(p->_messenger, 0);
                FUN_003f5410(p, DAT_0051a060, *tbl, DAT_00519b60, DAT_00519b68);
                sprintf(spA0, DAT_0051a2d0, *(int *)(igProperty_GetRecord(n, DAT_0051a2c8) + 12));
                FUN_003f5410(p, DAT_0051a2b8, *tbl, DAT_00519b60, DAT_0051a080);
                k += 1;
                i += 4;
                tbl += 1;
            } while (k < ((igIntList *)p->_playerNoList)->_count);
        }
        p->_receipt = 0;
        p->_st0 = p->_st0 + 1;
        p->_st3 = 0; p->_st2 = 0; p->_st1 = 0;
    case 1:
        switch (p->_st2) {
        case 0:
            k = 0;
            do {
                sprintf(sp90, DAT_0051a2d8, k);
                SEL(DAT_00519c28);
                APS(DAT_0051a2a8);
                APS(sp90);
                APS(DAT_00519b00);
                DSP(DAT_00519b08);
                k += 1;
            } while (k < 7);
            p->_editBit = 0;
            SEL(DAT_00519c28); APS(DAT_0051a2a8); APS(DAT_005199e0); APS(DAT_0051a1f8); DSP(DAT_0051a2e8);
            SEL(DAT_00519c28); APS(DAT_0051a2a8); APS(DAT_005199e0); APS(DAT_0051a210); DSP(DAT_00519f30);
            SEL(DAT_00519c28); APS(DAT_0051a2a8); APS(DAT_005199e0); APS(DAT_00519b78); DSP(DAT_00519b08);
            SEL(DAT_00519ba0); API(p->_playerNo); DSP(DAT_00519ba8);
            sprintf(sp80, DAT_0051a2d0, *(int *)(igProperty_GetRecord(beMessenger_GetObject(p->_messenger, 0), DAT_0051a2c8) + 12));
            SEL(DAT_00519c28); APS(DAT_0051a2b8); APS(DAT_005199e0); APS(sp80); DSP(DAT_00519f30);
            tbl = spE0.v;
            spE0 = DAT_004cf750[0];
            k2 = 0;
            if (0 < ((igIntList *)p->_playerNoList)->_count) {
                i2 = 0;
                do {
                    oe = *(int *)(((igIntList *)p->_playerNoList)->_data + i2);
                    SEL(DAT_00519ba0); API(oe); DSP(DAT_00519ba8);
                    n2 = beMessenger_GetObject(p->_messenger, 0);
                    {
                    RefX r11C((void *)*(int *)(*(int *)(*(int *)(igProperty_GetRecordFolder(n2, DAT_0051a1e8) + 12) + 16)));
                    if (r11C.p != 0) {
                        r11C.p->_refCount = r11C.p->_refCount + 1;
                    }
                    SEL(DAT_00519c28); APS(DAT_0051a060); APS(*tbl); APO(r11C.p); DSP(DAT_00519f30);
                    sprintf(sp70, DAT_0051a2d0, *(int *)(igProperty_GetRecord(n2, DAT_0051a2c8) + 12));
                    SEL(DAT_00519c28); APS(DAT_0051a2b8); APS(*tbl); APS(sp70); DSP(DAT_00519f30);
                    }
                    k2 += 1;
                    i2 += 4;
                    tbl += 1;
                } while (k2 < ((igIntList *)p->_playerNoList)->_count);
            }
            al = H::AllocFor(p);
            {
            float *q118;
            RefB r118((RefObj *)FUN_003b51b0(al));
            beNDMWWindow_BindContext(r118.p, p, p->_insight, p->_playerNo, 0);
            ObjectList_AppendRetained(p->_subWindow, r118.p);
            q118 = (float *)((beNDMWStatusSelectE1 *)r118.p)->_offsetPos;
            q118[0] = -121.0f;
            q118[1] = 109.0f;
            q118[2] = 0.0f;
            ((beNDMWStatusSelectE1 *)r118.p)->_selectMax = ((igIntList *)p->_playerNoList)->_count;
            ((beNDMWStatusSelectE1 *)r118.p)->_startPoint = p->_receipt;
            }
            p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
            p->_st2 = p->_st2 + 1;
            p->_st3 = 0;
        case 1:
            if (((igObjectList *)p->_subWindow)->_count != p->_nowProcKazu) {
                t = p->_retCode;
                if (t == -1) {
                    p->_st0 = p->_st0 + 1;
                    p->_st3 = 0; p->_st2 = 0; p->_st1 = 0;
                    return;
                }
                p->_receipt = t;
                switch (p->_receipt) {
                case 0:
                    spD0[0] = 0xC2F20000; spD0[1] = 0x42DA0000; spD0[2] = 0;
                    beNDMWWindow_PresentModel(p, DAT_00519d88, 0, DAT_00519cc8, 0, spD0);
                    break;
                case 1:
                    spC0[0] = 0xC2F20000; spC0[1] = 0x42DA0000; spC0[2] = 0;
                    beNDMWWindow_PresentModel(p, DAT_00519d88, 0, DAT_00519cd8, 0, spC0);
                    break;
                case 2:
                    spB0[0] = 0xC2F20000; spB0[1] = 0x42DA0000; spB0[2] = 0;
                    beNDMWWindow_PresentModel(p, DAT_00519d88, 0, DAT_00519ce8, 0, spB0);
                    break;
                }
                al = H::AllocFor(p);
                {
                Ref r114((RefObj *)FUN_003b45d0(al));
                beNDMWWindow_BindContext(r114.p, p, p->_insight, p->_playerNo, 3);
                ObjectList_AppendRetained(p->_subWindow, r114.p);
                FUN_004402e0(r114.p, p->_editBit, 1, DAT_0051a2d8);
                }
                p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
                SEL(DAT_00519ba0); API(p->_playerNo); DSP(DAT_00519ba8);
                mx = *(int *)(igProperty_GetRecord(beMessenger_GetObject(p->_messenger, 0), DAT_0051a2c8) + 12);
                if (mx >= 0x98967F) {
                    mx = 0x98967F;
                }
                o = ((int *)((igIntList *)p->_playerNoList)->_data)[p->_receipt];
                SEL(DAT_00519ba0); API(o); DSP(DAT_00519ba8);
                b = 0x98967F - *(int *)(igProperty_GetRecord(beMessenger_GetObject(p->_messenger, 0), DAT_0051a2c8) + 12);
                p->_editMax = (mx < b) ? mx : b;
                p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
                p->_st2 = p->_st2 + 1;
                p->_st3 = 0;
                return;
            }
            break;
        case 2:
            sw = p->_subWindow;
            if (((igObjectList *)sw)->_count == p->_nowProcKazu) {
                t = p->_retCode;
                if (t != -1) {
                    if (p->_st3 == t) {
                        beMessenger_SendNamed(p->_messenger, DAT_0051a2f0, DAT_0051a300, p->_playerNo, DAT_0051a310);
                        if (beMessenger_GetBool(p->_messenger, 0) & 0xFF) {
                            pad = bePadManager_GetPadForPlayer(p->_padManager, p->_playerNo);
                            c3 = ((bePadData *)pad)->_trigger;
                            c2 = ((bePadData *)pad)->_repeat;
                            c0 = ((bePadData *)pad)->_lTrg | ((bePadData *)pad)->_lRpt;
                            up = (c0 & 1) || ((c3 | c2) & 0x10);
                            dn = (c0 & 4) || ((c3 | c2) & 0x40);
                            if (up || dn) {
                                e = p->_editBit;
                                dig = 1;
                                t = 7 - p->_retCode;
                                cnt = t;
                                for (; cnt > 1; cnt--) { dig *= 10; }
                                if (up) {
                                    p->_editBit = p->_editBit + dig;
                                    c1 = p->_editMax;
                                    if (p->_editBit >= c1) {
                                        p->_editBit = c1;
                                    }
                                } else if (dn) {
                                    p->_editBit = p->_editBit - dig;
                                    if (p->_editBit <= 0) {
                                        p->_editBit = 0;
                                    }
                                }
                                c1 = p->_editBit;
                                if (c1 != e) {
                                    FUN_004402e0(((int *)((igObjectList *)p->_subWindow)->_data)[0], c1, t, DAT_0051a2d8, e, dig);
                                    SEL(DAT_0051a320); APS(DAT_0051a328); DSP(DAT_0051a338);
                                    return;
                                }
                            }
                        }
                    } else {
                        FUN_004402e0(((int *)((igObjectList *)sw)->_data)[0], p->_editBit, 7 - t, DAT_0051a2d8);
                        p->_st3 = p->_retCode;
                        return;
                    }
                }
            } else {
                if (p->_retCode == -1 || p->_editBit <= 0) {
                    beMessenger_SendNamed(p->_messenger, DAT_00519a90, DAT_00519d88, 0, DAT_00519a58);
                    p->_st2 = 0;
                    p->_st3 = 0;
                    return;
                }
                SEL(DAT_00519c28); APS(DAT_00519b50); APS(DAT_00519d98); APS(DAT_00519b00); DSP(DAT_00519b08);
                SEL(DAT_00519ba0); API(p->_playerNo); DSP(DAT_00519ba8);
                n = beMessenger_GetObject(p->_messenger, 0);
                t = *(int *)(igProperty_GetRecord(n, DAT_0051a2c8) + 12) - p->_editBit;
                *(int *)(igProperty_GetRecord(n, DAT_0051a2c8) + 12) = t;
                o = ((int *)((igIntList *)p->_playerNoList)->_data)[p->_receipt];
                SEL(DAT_00519ba0); API(o); DSP(DAT_00519ba8);
                n = beMessenger_GetObject(p->_messenger, 0);
                mx = *(int *)(igProperty_GetRecord(n, DAT_0051a2c8) + 12);
                t = mx + p->_editBit;
                *(int *)(igProperty_GetRecord(n, DAT_0051a2c8) + 12) = t;
                p->_st2 = p->_st2 + 1;
                p->_st3 = 0;
                return;
            }
            break;
        case 3:
            al = H::AllocFor(p);
            {
            RefA r110((RefObj *)FUN_003b4f50(al));
            beNDMWWindow_BindContext(r110.p, p, p->_insight, p->_playerNo, 0);
            ObjectList_AppendRetained(p->_subWindow, r110.p);
            beNDMWWindow_RunMessageScript(p, DAT_00519b90, 0x85);
            }
            p->_nowProcKazu = ((igObjectList *)p->_subWindow)->_count;
            p->_st2 = p->_st2 + 1;
            p->_st3 = 0;
            return;
        case 4:
            if (((igObjectList *)p->_subWindow)->_count != p->_nowProcKazu) {
                SEL(DAT_00519c28); APS(DAT_00519b50); APS(DAT_005199e0); APS(DAT_00519b00); DSP(DAT_00519b08);
                SEL(DAT_00519c10); API(p->_playerNo); DSP(DAT_00519c50);
                beMessenger_SendNamed(p->_messenger, DAT_00519a90, DAT_00519d88, 0, DAT_00519a58);
                p->_st2 = 0;
                p->_st3 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(p);
        beNDMWWindow_RequestChildrenClose(p);
        k = 0;
        p->_st0 = p->_st0 + 1;
        p->_st3 = 0; p->_st2 = 0; p->_st1 = 0;
        do {
            sprintf(sp60, DAT_0051a2d8, k);
            SEL(DAT_00519c28); APS(DAT_0051a2a8); APS(sp60); APS(DAT_00519b00); DSP(DAT_00519b08);
            k += 1;
        } while (k < 7);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            p->_isRun = 0;
        }
        break;
    }
}
