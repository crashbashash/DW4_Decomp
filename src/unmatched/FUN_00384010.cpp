class V108 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int); };
extern "C" void FUN_00384010(int arg0, int *arg1, int *arg2, int *arg3) {
    int temp_v0;

    arg2[1] = 0;
    arg2[0] = 0;
    arg2[2] = 0;
    arg3[1] = 3;
    arg3[0] = 0;
    arg3[2] = 0;
    temp_v0 = arg1[3];
    arg3[3] = temp_v0;
    arg2[3] = temp_v0;
    ((V108 *)arg1)->vX((int)arg2, 1);
    ((V108 *)arg1)->vX((int)arg3, 1);
}
