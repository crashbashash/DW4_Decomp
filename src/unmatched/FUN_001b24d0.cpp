struct V3 { float x, y, z; };
struct X { char pad[4]; int f4; V3 a; V3 b; };
extern "C" {
X *FUN_0018a660(...);
int FUN_00190060(...);
int FUN_001b21d0(...);
int FUN_001b23b0(...);
int igVertexArray2__FindVertexData(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int FUN_001b24d0(int arg0, int arg1);
}
int FUN_001b24d0(int arg0, int arg1) {
    V3 sp48;
    V3 sp38;
    X *volatile sp5C;
    X *sp58;
    X *t;
    int temp_s0;

    sp5C = FUN_0018a660(igObject_GetAllocator());
    FUN_001b21d0(arg1, &sp48, &sp38);
    t = sp5C;
    t->a = sp48;
    t = sp5C;
    t->b = sp38;
    t = sp5C;
    FUN_00190060(arg0, t);
    FUN_001b23b0(&sp58, arg1);
    temp_s0 = igVertexArray2__FindVertexData(sp58, 5, 0);
    t = sp58;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        t = sp58;
        if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    t = sp5C;
    temp_s0 = !temp_s0 & 0xFF;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    return temp_s0;
}
