extern "C" {
void *FUN_002ba650(...);
int FUN_00326330(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_004fb410[4];
}
struct R4 { int v; R4() {} R4(int x) { v = x; } };
class Ob { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R4 a92(); virtual R4 a96(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual R4 a132(int); int pad4; };
struct Pool { char pad[116]; Ob *f116; char p2[20]; unsigned f136; };
struct Rel { static inline void go(Ob *object) {
    if (object) {
        object->pad4 = object->pad4 - 1;
        if (((unsigned long long)(long long)object->pad4 & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" R4 Gap__Core__igPageMemoryPool__vfunc_34(Pool *arg1, int arg2);
R4 Gap__Core__igPageMemoryPool__vfunc_34(Pool *arg1, int arg2) {
    Ob * volatile sp5C;
    Ob * volatile sp58;
    Ob *s0;
    int a1;
    if (arg2 != 0) {
        a1 = *(int *)((char *)arg1 + 140) | 4;
    } else {
        a1 = *(int *)((char *)arg1 + 140) & ~4;
    }
    FUN_00326330(arg1, a1);
    if ((arg2 & 0xFF) == 0) {
        sp5C = arg1->f116;
        s0 = sp5C;
        if (s0 != 0) {
            s0->pad4 = s0->pad4 + 1;
        }
        Rel::go(arg1->f116);
        arg1->f116 = 0;
        s0 = sp5C;
        if (s0 != 0) {
            s0->a132(1);
            sp5C->a96();
        }
        s0 = sp5C;
        Rel::go(s0);
    } else if ((arg2 & 0xFF) == 1) {
        if (arg1->f116 != 0) {
            return DAT_004fb410[0];
        }
        sp58 = (Ob *)FUN_002ba650(igObject_GetAllocator(arg1));
        sp58->a92();
        s0 = sp58;
        if (s0 != 0) {
            s0->pad4 = s0->pad4 + 1;
        }
        Rel::go(arg1->f116);
        arg1->f116 = s0;
        s0 = sp58;
        Rel::go(s0);
    }
    return DAT_004fb410[0];
}
