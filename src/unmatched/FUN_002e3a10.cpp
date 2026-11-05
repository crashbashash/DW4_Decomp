extern "C" {
void **igIntMetaField_GetDefaultDescriptor(...);
int FUN_002e3a10(void *arg0, void *arg1);
}
class DW4VC_208_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int *, int); };
int FUN_002e3a10(void *arg0, void *arg1) {
    int sp1C;
    void **temp_v0;

    sp1C = *(int *)((char *)(arg1) + 4);
    if (*(unsigned char *)((char *)(arg0) + 168) != 0) {
        temp_v0 = (void **)(igIntMetaField_GetDefaultDescriptor());
        ((DW4VC_208_2 *)(temp_v0))->vX(&sp1C, 1);
    }
    return sp1C;
}
