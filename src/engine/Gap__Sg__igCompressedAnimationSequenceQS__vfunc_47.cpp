extern "C" {
int FUN_00192f00(int *, int *, int *, float);
void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_47(void *arg0, int *arg1, int arg2, int arg3, float fparg0);
}
class DW4VC_184_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int vX(int, int *); };
void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_47(void *arg0, int *arg1, int arg2, int arg3, float fparg0) {
    int sp60[4];
    int sp50[4];

    if (*(unsigned char *)((char *)(arg0) + 57) == 0) {
        ((DW4VC_184_2 *)(((char *)(arg0) + 0)))->vX(arg2, arg1);
        return;
    }
    ((DW4VC_184_2 *)(((char *)(arg0) + 0)))->vX(arg2, &sp60[0]);
    ((DW4VC_184_2 *)(((char *)(arg0) + 0)))->vX(arg3, &sp50[0]);
    FUN_00192f00(arg1, &sp60[0], &sp50[0], fparg0);
}
