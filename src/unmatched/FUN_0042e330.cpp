#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int List_Resize(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beDataBase_GetRecordString(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_GetObjectCount(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendNamed(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_SendModelSequence(...);
int igProperty_GetRecordArray(...);
int strcmp(...);
extern int DAT_004cf9f0[4];
extern int DAT_004cf9f8[4];
extern int DAT_0051b1c8[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b5d8[4];
extern int DAT_0051b5e8[4];
extern int DAT_0051b620[4];
extern int DAT_0051b6b0[4];
extern int DAT_0051b8d8[4];
extern int DAT_0051b908[4];
extern int DAT_0051b918[4];
extern int DAT_0051b920[4];
extern int DAT_0051b930[4];
extern int DAT_0051b938[4];
extern int DAT_0051b948[4];
extern int DAT_00586f20[4];
}
/* Owning string reference (count at p[-1], header at p[-2]); one class for all four retail holders, whose destructor
 * is the shared copy at 0x130720.  Str::intern already hands out a retained string, so the constructor adopts it. */
struct StringRef {
    int p;
    StringRef() {}
    StringRef(int s) { p = s; }
    ~StringRef() { int s = p; if (s != 0) { int *hd = (int *)s - 2; int cnt = ((int *)s)[-1] - 1; ((int *)s)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
};
extern "C" StringRef StringList_CopyRetained(void *list, int index);
struct Str { static inline int intern(int *s) {
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool)
                pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = StringPool_Intern(DAT_00586f20[0], s);
    }
    return ref;
}
static inline void release(int ref) {
    int *header;
    int count;
    if (ref) {
        header = (int *)(ref - 8);
        count = *(int *)(ref - 4) - 1;
        *(int *)(ref - 4) = count;
        if (!count)
            StringChunk_ReleaseHeader(*header, header);
    }
} };
/* matching construct: frame-slot order.  Retail's holders sit at 0x98 (copy of the card name), 0x94 (branch 2), 0x90
 * (branch 1) and 0x8c (branch 3); the branch-1 and branch-3 holders are locals of static inline members, which are
 * allocated below the caller's.  The shared loop variables are passed by reference so register order is unchanged.
 * inline_depth(8) keeps the nested intern/destructor inline.  Found by trial (no permuter). */
struct Slots {
    static inline void StoreCardName1(beNDMWShopCtrlA1 *arg0, int &s0, int &o, igDataList *&l, int &n, int *&arr, int &t, int *&p) {
        StringRef sp90(Str::intern(&DAT_0051b948[0]));
        l = ((igDataList *)arg0->_cardInfoList);
        n = l->_count;
        if (n != 0 && s0 >= 0 && s0 < n) {
            arr = (int *)l->_data;
            t = sp90.p;
            p = (int *)((char *)arr + o);
            if (t) *(int *)(t - 4) = *(int *)(t - 4) + 1;
            Str::release(*p);
            *p = sp90.p;
        }
    }
    static inline void StoreCardName3(beNDMWShopCtrlA1 *arg0, int &s0, int &o, igDataList *&l, int &n, int *&arr, int &t, int *&p3) {
        StringRef sp8c(Str::intern(&DAT_0051b938[0]));
        l = ((igDataList *)arg0->_cardInfoList);
        n = l->_count;
        if (n != 0 && s0 >= 0 && s0 < n) {
            arr = (int *)l->_data;
            t = sp8c.p;
            p3 = (int *)((char *)arr + o);
            if (t) *(int *)(t - 4) = *(int *)(t - 4) + 1;
            Str::release(*p3);
            *p3 = sp8c.p;
        }
    }
};
struct Arr { char p0[16]; unsigned char *f16; };
struct Rec { char p0[12]; Arr *f12; };
extern "C" void FUN_0042e330(beNDMWShopCtrlA1 *arg0);
void FUN_0042e330(beNDMWShopCtrlA1 *arg0) {
    char buf[2];
    igDataList *l;
    int s5;
    Arr *s6;
    int ref;
    int s1;
    int s0;
    int n;
    int *arr;
    int t;
    int *p;
    int *p2;
    int *p3;
    int s4;
    int o;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    s6 = ((Rec *)igProperty_GetRecordArray(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b908[0]))->f12;
    s4 = arg0->_retCode;
    beMessenger_SendNamed(arg0->_messenger, &DAT_0051b5d8[0], &DAT_0051b918[0], 0, &DAT_0051b5e8[0]);
    if (beMessenger_GetObjectCount(arg0->_messenger) > 0) {
        s1 = beMessenger_GetObject(arg0->_messenger, 0);
    } else {
        return;
    }
    buf[1] = 0;
    buf[0] = s4 + 49;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b8d8[0]);
    beMessenger_AppendString(arg0->_messenger, &DAT_0051b1c8[0]);
    beMessenger_AppendString(arg0->_messenger, buf);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b6b0[0]);
    switch (s4) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
        s0 = 0;
        o = 0;
        s4 = s4 * 6;
        do {
            {
            StringRef sp98 = StringList_CopyRetained(((igDataList *)arg0->_cardInfoList), s0);
            s5 = *(int *)(((igIntList *)arg0->_cardRamNoList)->_data + o);
            if (s4 > 49) {
                beNDMWWindow_SendModelSequence(arg0, sp98.p, s5, &DAT_0051b620[0]);
                Slots::StoreCardName1(arg0, s0, o, l, n, arr, t, p);
                l = ((igDataList *)arg0->_cardRamNoList);
                n = l->_count;
                if (n != 0 && s0 >= 0 && s0 < n) *(int *)(l->_data + o) = DAT_004cf9f0[0];
            } else if (s6->f16[s4] != 0) {
                if (s5 != -1) beNDMWWindow_SendModelSequence(arg0, sp98.p, s5, &DAT_0051b620[0]);
                ref = beDataBase_GetRecordString(s1, s4, &DAT_0051b920[0]);
                {
                StringRef sp94(Str::intern((int *)ref));
                beNDMWWindow_PresentModelAtOrigin(arg0, sp94.p, 0, beDataBase_GetRecordString(s1, s4, &DAT_0051b930[0]), 0);
                l = ((igDataList *)arg0->_cardInfoList);
                n = l->_count;
                if (n != 0 && s0 >= 0 && s0 < n) {
                    arr = (int *)l->_data;
                    t = sp94.p;
                    p2 = (int *)((char *)arr + o);
                    if (t) *(int *)(t - 4) = *(int *)(t - 4) + 1;
                    Str::release(*p2);
                    *p2 = sp94.p;
                }
                l = ((igDataList *)arg0->_cardRamNoList);
                n = l->_count;
                if (n != 0 && s0 >= 0 && s0 < n) *(int *)(l->_data + o) = DAT_004cf9f8[0];
                }
            } else {
                if (s5 != -1) {
                    if (strcmp(sp98.p, &DAT_0051b938[0]) == 0) {
                        goto next;
                    }
                    beNDMWWindow_SendModelSequence(arg0, sp98.p, s5, &DAT_0051b620[0]);
                }
                beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b938[0], s0, beDataBase_GetRecordString(s1, s0, &DAT_0051b930[0]), 0);
                Slots::StoreCardName3(arg0, s0, o, l, n, arr, t, p3);
                l = ((igDataList *)arg0->_cardRamNoList);
                n = l->_count;
                if (n != 0 && s0 >= 0 && s0 < n) *(int *)(l->_data + o) = s0;
            }
            }
next:
            s0++;
            s4++;
            o += 4;
        } while (s0 < 6);
        break;
    }
}
