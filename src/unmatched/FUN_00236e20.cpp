extern "C" {
int ObjectList_RemoveFirstRetained(...);
void FUN_00236e20(void *arg0, void **arg1);
}
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
void FUN_00236e20(void *arg0, void **arg1) {
    int sp3C;

    ((DW4VC_96_1 *)(arg1))->vX((int)(arg0));
    ObjectList_RemoveFirstRetained(&sp3C, *(int *)((char *)(arg0) + 104), arg1, 0);
}
