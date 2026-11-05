struct T { int w0; int refs; };
extern "C" {
int FUN_001cb010(...);
int FUN_001cd9f0(...);
int FUN_002da990(...);
int igObject_Destroy(...);
void FUN_001cb1f0(int arg0, int arg1, int arg2, int arg3, void **arg4, int arg5);
}
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
void FUN_001cb1f0(int arg0, int arg1, int arg2, int arg3, void **arg4, int arg5) {
    T *sp6C;

    FUN_001cd9f0(&sp6C, arg0, arg1);
    if (sp6C != 0) {
        ((DW4VC_96_1 *)(arg4))->vX((int)(sp6C));
        FUN_001cb010(arg0, sp6C, arg5);
        FUN_002da990(sp6C, arg2, arg3, 1);
    }
    T *p = sp6C;
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long) ((long long) p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
}
