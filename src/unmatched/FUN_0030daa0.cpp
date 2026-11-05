extern "C" {
int List_Reserve(int *, int, int);
int FUN_0030cf20(int, int);
int FUN_0030cf30(int, int);
int FUN_0030cf40(int);
}
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); };
extern "C" void FUN_0030daa0(int *arg0) {
    int *temp_a0;
    int temp_a1;
    temp_a1 = arg0[2] * 4;
    temp_a0 = (int *)arg0[7];
    if (temp_a1 >= temp_a0[2]) {
        List_Reserve(temp_a0, temp_a1, 4);
    }
    ((A *)arg0)->vX(arg0[3]);
    FUN_0030cf20(arg0[9], arg0[2] * 4);
    FUN_0030cf30(arg0[9], arg0[2]);
    FUN_0030cf40(arg0[9]);
    FUN_0030cf20(arg0[10], 0x1000);
    FUN_0030cf30(arg0[10], 0x100);
    FUN_0030cf40(arg0[10]);
}

