/* Matches only under top-down inlining (`-inline level=8`). Under its unit's bottom-up inlining the
 * `Slots` members pass `inline_max_size`, so the string intern and release they hold stay calls. */
#include "dw4/reflected.h"
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetObject(...);
extern "C" int beMessenger_GetObjectCount(...);
extern "C" int beMessenger_SendNamed(...);
extern "C" int FUN_002eb010(...);
extern "C" int StringPool_Construct(...);
extern "C" char * StringPool_Intern(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" char * beDataBase_GetRecordString(...);
extern "C" int beNDMWWindow_PresentModelAtOrigin(...);
extern "C" int igProperty_GetRecordArray(...);
extern "C" int beNDMWWindow_SendModelSequence(...);
extern "C" int strcmp(...);
extern "C" int DAT_0051b1c8[4];
extern "C" int DAT_0051b398[4];
extern "C" int DAT_0051b3c0[4];
extern "C" int DAT_0051b3e8[4];
extern "C" int DAT_0051b5d8[4];
extern "C" int DAT_0051b5e8[4];
extern "C" int DAT_0051b620[4];
extern "C" int DAT_0051b6b0[4];
extern "C" int DAT_0051b8d8[4];
extern "C" int DAT_0051b908[4];
extern "C" int DAT_0051b918[4];
extern "C" int DAT_0051b920[4];
extern "C" int DAT_0051b930[4];
extern "C" int DAT_0051b938[4];
extern "C" int DAT_00586f20[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(int s) : p((char *)s) {}
    ~StringRef() { release(); }
    void release() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" StringRef StringList_CopyRetained(...);
struct Arr { char p0[16]; unsigned char *f16; };
struct Rec_42df70 { char p0[12]; Arr *f12; };
extern "C" int DAT_004cf9f0[4];
extern "C" int DAT_004cf9f8[4];
extern "C" int DAT_0051b948[4];
struct Str_42e330 { static inline int intern(int *s) {
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
        ref = ((int)StringPool_Intern(DAT_00586f20[0], s));
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
        StringRef sp90(Str_42e330::intern(&DAT_0051b948[0]));
        l = ((igDataList *)arg0->_cardInfoList);
        n = l->_count;
        if (n != 0 && s0 >= 0 && s0 < n) {
            arr = (int *)l->_data;
            t = (int)sp90.p;
            p = (int *)((char *)arr + o);
            if (t) *(int *)(t - 4) = *(int *)(t - 4) + 1;
            Str_42e330::release(*p);
            *p = (int)sp90.p;
        }
    }
    static inline void StoreCardName3(beNDMWShopCtrlA1 *arg0, int &s0, int &o, igDataList *&l, int &n, int *&arr, int &t, int *&p3) {
        StringRef sp8c(Str_42e330::intern(&DAT_0051b938[0]));
        l = ((igDataList *)arg0->_cardInfoList);
        n = l->_count;
        if (n != 0 && s0 >= 0 && s0 < n) {
            arr = (int *)l->_data;
            t = (int)sp8c.p;
            p3 = (int *)((char *)arr + o);
            if (t) *(int *)(t - 4) = *(int *)(t - 4) + 1;
            Str_42e330::release(*p3);
            *p3 = (int)sp8c.p;
        }
    }
};
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
    s6 = ((Rec_42df70 *)igProperty_GetRecordArray(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b908[0]))->f12;
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
                ref = ((int)beDataBase_GetRecordString(s1, s4, &DAT_0051b920[0]));
                {
                StringRef sp94(Str_42e330::intern((int *)ref));
                beNDMWWindow_PresentModelAtOrigin(arg0, sp94.p, 0, ((int)beDataBase_GetRecordString(s1, s4, &DAT_0051b930[0])), 0);
                l = ((igDataList *)arg0->_cardInfoList);
                n = l->_count;
                if (n != 0 && s0 >= 0 && s0 < n) {
                    arr = (int *)l->_data;
                    t = (int)sp94.p;
                    p2 = (int *)((char *)arr + o);
                    if (t) *(int *)(t - 4) = *(int *)(t - 4) + 1;
                    Str_42e330::release(*p2);
                    *p2 = (int)sp94.p;
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
                beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b938[0], s0, ((int)beDataBase_GetRecordString(s1, s0, &DAT_0051b930[0])), 0);
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
