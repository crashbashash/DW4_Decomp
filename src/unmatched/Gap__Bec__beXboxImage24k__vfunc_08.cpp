/* Member field accessed through the class so the base register is not folded; verified by tools/verify.py. */
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(...);
int Memory_FreeBuffer(...);
int igMetaObject_CountInstances(...);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad4; int f8; };
extern "C" void Gap__Bec__beXboxImage24k__vfunc_08(DW4VC_88_0 *arg0) {
    int temp_a0;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->f8 = 0;
    igMetaObject_CountInstances(arg0->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
