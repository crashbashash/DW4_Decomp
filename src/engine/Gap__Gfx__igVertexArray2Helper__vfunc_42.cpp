class Y { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); char pad[12]; int *f16; };
struct X { char pad[12]; Y *f12; };
struct A { char pad[12]; int f12; };
extern "C" {
void *igVertexArray2__FindVertexData(...);
extern int DAT_00561098[4];
extern int DAT_00586858[4];
int Gap__Gfx__igVertexArray2Helper__vfunc_42(A *arg0, int arg1);
}
int Gap__Gfx__igVertexArray2Helper__vfunc_42(A *arg0, int arg1) {
    int temp_s0;
    Y *temp_a0;
    Y *temp_a0_2;
    X *temp_v0;
    int temp_s0_2;

    temp_v0 = (X *)igVertexArray2__FindVertexData(arg0->f12, 2, 0);
    temp_a0 = temp_v0->f12;
    temp_s0 = DAT_00586858[0];
    if (temp_s0 == temp_a0->vX()) {
        return temp_v0->f12->f16[arg1];
    }
    temp_a0_2 = temp_v0->f12;
    temp_s0_2 = DAT_00561098[0];
    if (temp_s0_2 == temp_a0_2->vX()) {
        return temp_v0->f12->f16[arg1];
    }
    return 0;
}
