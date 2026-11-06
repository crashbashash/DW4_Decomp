class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int, int); };
extern "C" void Gap__Gui__igEventDispatcher__vfunc_41(int *arg0, int arg1, int arg2) {
    int temp_s1;
    int var_s0;
    A *temp_a0;
    temp_s1 = *(int *)(*(int *)((char *)(arg0[3]) + 8) + 8);
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        temp_a0 = (A *)(*(int *)(*(int *)(*(int *)((char *)(arg0[3]) + 8) + 16) + (var_s0 * 4)));
        if (temp_a0->vX(arg2, 0) & 0xFF) {
            break;
        }
    }
}

