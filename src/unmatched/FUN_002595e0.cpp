#include "dw4/reflected.h"
typedef igObject Obj;
/* matching construct: out-of-line ctor/dtor classes reproduce the retail unwind table (retail 0x2595e0 table 0x542b5c: App dtor 0x234b90, Blk dtor 0x25a330, scope guard dtor 0x2599b0) */
struct App { char p[232]; int f232; int f236; App(); ~App(); };
struct Blk { char p[64]; Blk(); ~Blk(); };
struct G { int f0; char p[212]; unsigned char f216; char p2[15]; int f232; int f236; };
extern "C" {
int FUN_00100610(G *);
G *FUN_001007e0(int);
int FUN_00165d20(int);
int FUN_00234d70(App *, int, int *);
G *FUN_00238110(G *);
int FUN_002590c0();
int FUN_00259a20();
int FUN_00259cd0(int);
int FUN_00259d10();
int FUN_00259f90(Blk *, int, int);
int FUN_0025a580(Blk *);
int FUN_0025a8c0(Blk *);
int FUN_002d16a0(int);
int FUN_002d1770();
int FUN_002f8a20();
int Memory_GetAllocatorBySelector(int);
void StringChunk_ReleaseHeader(int, int *);
igAnimationCombinerBoneInfoPool *igAnimationCombinerBoneInfoPool_Create(int);
Obj *igAnimationStatePool_Create(int);
Obj *igEnbayaContextPool_Create(int);
void igObject_Destroy(Obj *);
extern int DAT_004ec870[4];
extern igAnimationCombinerBoneInfoPool *DAT_00562528[4];
extern Obj *DAT_00562540[4];
extern Obj *DAT_00562718[4];
extern G *DAT_0056dc50[4];
extern int DAT_00586fd8[4];
extern int DAT_00586fe0[4];
extern int DAT_00586fe8[4];
extern int DAT_00586ff0[4];
extern int DAT_00587108[4];
extern int DAT_00587338[4];
extern int *DAT_00587340[4];
extern char GPR_0055499c;
extern char GPR_005549a0;
extern char GPR_005549b8;
extern unsigned char GPR_00554c14;
int FUN_002595e0(int arg0, int *arg1);
}
struct Guard { ~Guard() { FUN_002d1770(); } };
struct U {
    static inline int alloc(int fallback) {
        if (GPR_00554c14) return fallback;
        else return Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    static inline void relg(Obj **g) {
        Obj *o = g[0];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)(long long)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o);
        }
    }
    static inline void relstr(int *slot) {
        if (slot != 0) {
            int v = *slot;
            if (v != 0) {
                int *hd = (int *)(v - 8);
                int c = ((int *)v)[-1] - 1;
                ((int *)v)[-1] = c;
                if (c == 0) StringChunk_ReleaseHeader(*hd, hd);
            }
        }
    }
};
extern "C" int FUN_002595e0(int arg0, int *arg1) {
    int a;
    G *s0;
    FUN_00259a20();
    FUN_00259cd0(*arg1);
    DAT_00587338[0] = 2;
    GPR_0055499c = 0;
    DAT_00587340[0] = DAT_004ec870;
    GPR_005549b8 = 1;
    GPR_005549a0 = 0;
    DAT_00586fd8[0] = 0x40000;
    DAT_00586fe0[0] = 0x4000;
    DAT_00586fe8[0] = 0xA0000;
    DAT_00586ff0[0] = 0x69000;
    FUN_002d16a0(0xC80);
    Guard guard;
    FUN_00259d10();
    FUN_002590c0();
    App sp70;
    FUN_00234d70(&sp70, arg0, arg1);
    a = U::alloc(FUN_002f8a20());
    FUN_00165d20(a);
    U::relg(DAT_00562718);
    DAT_00562718[0] = 0;
    a = U::alloc(FUN_002f8a20());
    U::relg(DAT_00562718);
    DAT_00562718[0] = igEnbayaContextPool_Create(a);
    a = U::alloc(FUN_002f8a20());
    U::relg((Obj **)DAT_00562528);
    DAT_00562528[0] = igAnimationCombinerBoneInfoPool_Create(a);
    DAT_00562528[0]->_resetMode = 0;
    a = U::alloc(FUN_002f8a20());
    U::relg(DAT_00562540);
    DAT_00562540[0] = igAnimationStatePool_Create(a);
    Blk sp30;
    FUN_00259f90(&sp30, sp70.f236, sp70.f232);
    if (DAT_0056dc50[0] == 0) {
        G *v = FUN_001007e0(240);
        if (v != 0) v = FUN_00238110(v);
        DAT_0056dc50[0] = v;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    if (DAT_0056dc50[0]->f216 != 0) FUN_0025a8c0(&sp30);
    else FUN_0025a580(&sp30);
    if (DAT_0056dc50[0] != 0) {
        int t = DAT_0056dc50[0]->f232 - 1;
        DAT_0056dc50[0]->f232 = t;
        if (t <= 0) {
            s0 = DAT_0056dc50[0];
            if (s0 != 0) {
                U::relstr(&s0->f236);
                U::relstr((int *)s0);
                FUN_00100610(s0);
            }
            DAT_0056dc50[0] = 0;
        }
    }
    return 0;
}
