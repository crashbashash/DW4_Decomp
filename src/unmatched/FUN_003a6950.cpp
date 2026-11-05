extern "C" {
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;
int FUN_00331fb0(...);
int FUN_003320d0(...);
void *FUN_003350f0(...);
void *FUN_00367490(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
}
struct Obj { int w0; unsigned refs; Obj *w8; Obj *w12; int w16; int w20; };
struct Rel {
    static inline void go(Obj *p) {
        if (p != 0) {
            p->refs = p->refs - 1;
            if ((p->refs & 0x7fffff) == 0) igObject_Destroy(p);
        }
    }
};
extern "C" int FUN_003a6950(Obj *o, int mode) {
    if (mode < 0) {
        int a = igObject_GetAllocator(o);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587108[0]);
        Rel::go(o->w12);
        o->w12 = (Obj *)FUN_00367490(a);
        Rel::go(o->w8);
        o->w8 = 0;
        o->w16 = 3;
    } else {
        int a = igObject_GetAllocator(o);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587108[0]);
        Rel::go(o->w8);
        o->w8 = (Obj *)FUN_003350f0(a);
        Rel::go(o->w12);
        o->w12 = 0;
        o->w16 = 1;
        int rate = (mode == 2) ? 0xBB80 : 0x5DC0;
        if (FUN_00331fb0(o->w8, mode, 1, 2, rate) == 0) return 0;
        if (FUN_003320d0(o->w8, mode, 1, 2, rate, 0) == 0) return 0;
    }
    o->w20 = -999;
    return 1;
}
