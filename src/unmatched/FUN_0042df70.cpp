#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int List_Resize(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int beDataBase_GetRecordString(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_GetObjectCount(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendNamed(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int igProperty_GetRecordArray(...);
extern int DAT_004cf9e8[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b5d8[4];
extern int DAT_0051b5e8[4];
extern int DAT_0051b908[4];
extern int DAT_0051b918[4];
extern int DAT_0051b920[4];
extern int DAT_0051b930[4];
extern int DAT_0051b938[4];
extern int DAT_00586f20[4];
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(int s) : p((char *)s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
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
};
struct Arr { char p0[16]; unsigned char *f16; };
struct Rec { char p0[12]; Arr *f12; };
extern "C" void FUN_0042df70(beNDMWShopCtrlA1 *arg0);
void FUN_0042df70(beNDMWShopCtrlA1 *arg0) {
    Arr *s2;
    int s1;
    int s4;
    int s0;
    int c;
    int tt;
    igIntList *l;
    int c2;
    igIntList *l2;
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
    s2 = ((Rec *)igProperty_GetRecordArray(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b908[0]))->f12;
    beMessenger_SendNamed(arg0->_messenger, &DAT_0051b5d8[0], &DAT_0051b918[0], 0, &DAT_0051b5e8[0]);
    if (beMessenger_GetObjectCount(arg0->_messenger) > 0) {
        s1 = beMessenger_GetObject(arg0->_messenger, 0);
    } else {
        return;
    }
    {
        s0 = 0;
        do {
            beDataBase_GetRecordString(s1, s0, &DAT_0051b920[0]);
            beDataBase_GetRecordString(s1, s0, &DAT_0051b930[0]);
            if (s2->f16[s0] != 0) {
                s4 = beDataBase_GetRecordString(s1, s0, &DAT_0051b920[0]);
                tt = Str::intern((int *)s4);
                StringRef name(tt);
                beNDMWWindow_PresentModelAtOrigin(arg0, name.p, 0, beDataBase_GetRecordString(s1, s0, &DAT_0051b930[0]), 0);
                {
                    StringRef copy((int)name.p);
                    tt = (int)copy.p;
                    if (tt)
                        *(int *)(tt - 4) = *(int *)(tt - 4) + 1;
                    StringList_AppendRetained(arg0->_cardInfoList, copy);
                }
                l = (igIntList *)arg0->_cardRamNoList;
                c = l->_count;
                if (c < l->_capacity) {
                    l->_count = *(volatile int *)&l->_count + 1;
                } else {
                    List_Resize(l, c + 1, 4);
                }
                ((int *)l->_data)[c] = DAT_004cf9e8[0];
            } else {
                beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051b938[0], s0, beDataBase_GetRecordString(s1, s0, &DAT_0051b930[0]), 0);
                { int tok = Str::intern(&DAT_0051b938[0]); StringList_AppendRetained(arg0->_cardInfoList, StringRef(tok)); }
                l2 = (igIntList *)arg0->_cardRamNoList;
                c2 = l2->_count;
                if (c2 < l2->_capacity) {
                    l2->_count = *(volatile int *)&l2->_count + 1;
                } else {
                    List_Resize(l2, c2 + 1, 4);
                }
                ((int *)l2->_data)[c2] = s0;
            }
            s0++;
        } while (s0 < 6);
    }
}
