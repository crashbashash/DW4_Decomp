extern "C" {
int FUN_00301590(...);
void Gap__Core__igObjectDirEntry__vfunc_38(void *arg0);
}
struct DW4RT { char pad[64]; int (*fn)(); };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual DW4RT *vX(); };
void Gap__Core__igObjectDirEntry__vfunc_38(void *arg0) {
    DW4VC_88_0 *a = *(DW4VC_88_0 **)((char *)arg0 + 24);
    if (a != 0) {
        int (*f)() = a->vX()->fn;
        if (f != 0) {
            FUN_00301590(arg0, f());
        }
    }
}
