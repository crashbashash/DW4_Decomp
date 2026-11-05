extern "C" {
int FUN_00192810(...);
int Matrix44_SetTranslation(...);
int FUN_001c0810(void **arg0, int arg1, int arg2, int arg3);
}
class DW4VC_108_4 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int, int); };
int FUN_001c0810(void **arg0, int arg1, int arg2, int arg3) {
    int sp30[4];
    int sp40[4];
    int temp_s0;

    temp_s0 = ((DW4VC_108_4 *)(arg0))->vX((int)sp30, (int)sp40, (int)(arg2), (int)(arg3)) & 0xFF;
    FUN_00192810(sp30, arg1);
    Matrix44_SetTranslation(arg1, sp40);
    return temp_s0;
}
