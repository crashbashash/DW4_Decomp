extern "C" {

void Gap__Core__igMediaFile__vfunc_28(void *arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4);
}
class DW4VC_108_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
class DW4VC_116_5 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, int, int, int, int); };
void Gap__Core__igMediaFile__vfunc_28(void *arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4) {
    void **temp_a0;

    if (*(unsigned char *)((char *)(arg0) + 45) == 0) {
        arg3(arg4, -1);
    }
    if (*(unsigned char *)((char *)(arg0) + 44) == 1) {
        temp_a0 = (void **)(*(int *)((char *)(arg0) + 64));
        ((DW4VC_116_5 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 24)), (int)(arg1), (int)(arg2), (int)(arg3), (int)(arg4));
    }
    arg3(arg4, ((DW4VC_108_3 *)(((char *)(arg0) + 0)))->vX((int)(arg1), (int)(1), (int)(arg2)));
}
