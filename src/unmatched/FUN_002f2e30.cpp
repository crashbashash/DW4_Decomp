extern "C" {
void *FUN_002c01f0(int);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
extern int DAT_004fb410[4];
extern void * DAT_00586dc8[4];
}
struct R { int v; R() {} R(int x) { v = x; } };
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
class Child { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual R vA(int, int); };
class Self { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual R vB(int, int); };
struct OB { int vt; int a4; int a8; int a12; RO *f16; };
extern "C" {
R FUN_002f2e30(OB *arg1, int arg2, int arg3) {
    int temp_s0;
    RO *temp_a0;
    if (arg1->f16 == 0) {
        temp_s0 = igObject_GetAllocator(arg1);
        temp_a0 = arg1->f16;
        if (temp_a0 != 0) {
            temp_a0->u.w = temp_a0->u.w - 1;
            if (temp_a0->u.b.cnt == 0) igObject_Destroy(temp_a0);
        }
        arg1->f16 = (RO *)FUN_002c01f0(temp_s0);
    }
    if (arg2 == 0) {
        arg2 = *(int *)((char *)DAT_00586dc8[0] + 56);
    }
    R sp6C = ((Child *)arg1->f16)->vA(arg2, arg3);
    if (sp6C.v == DAT_004fb410[0]) {
        R sp68 = ((Self *)arg1)->vB((int)arg1->f16, 1);
        sp6C = sp68;
    }
    return sp6C;
}
}
