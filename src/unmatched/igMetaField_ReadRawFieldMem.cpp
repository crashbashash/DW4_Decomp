class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void vX(int, int); char pad4[16]; unsigned short f20; };
extern "C" {
int memcpy(int, int, int);
unsigned short igMetaField_ReadRawFieldMem(C *arg0, int arg1, int arg2, int arg3, int arg4);
}
unsigned short igMetaField_ReadRawFieldMem(C *arg0, int arg1, int arg2, int arg3, int arg4) {
    memcpy(arg1, arg2, arg0->f20);
    if (arg4 != 0) {
        arg0->vX(arg1, 1);
    }
    return arg0->f20;
}
