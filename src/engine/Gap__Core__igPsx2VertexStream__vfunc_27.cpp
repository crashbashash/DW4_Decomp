class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); int pad4[2]; int f12; unsigned char f16; char pad17[23]; long long f40; char pad48[80]; int f128; int f132; int f136; };
extern "C" {
int FUN_00180020(...);
int FUN_001eeda0(...);
int Gap__Core__igVertexStream__vfunc_27(...);
int Memory_FreeBuffer(...);
void Gap__Core__igPsx2VertexStream__vfunc_27(A *arg0);
}
void Gap__Core__igPsx2VertexStream__vfunc_27(A *arg0) {
    int temp_a0;
    int temp_a0_2;

    if ((arg0->f16 != 0) && (arg0->vX() != 0)) {
        FUN_001eeda0(arg0->f128);
        arg0->f12 = 0;
    } else {
        if (arg0->f40 != 0) {
            FUN_00180020(arg0);
        }
        arg0->f12 = 0;
    }
    arg0->f128 = 0;
    temp_a0 = arg0->f132;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
        arg0->f132 = 0;
    }
    temp_a0_2 = arg0->f136;
    if (temp_a0_2 != 0) {
        Memory_FreeBuffer(temp_a0_2);
        arg0->f136 = 0;
    }
    Gap__Core__igVertexStream__vfunc_27(arg0);
}
