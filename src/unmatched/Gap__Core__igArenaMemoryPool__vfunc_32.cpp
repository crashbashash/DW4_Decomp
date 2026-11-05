extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_32(void *arg0);
}
class AP { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(); char pad[116-4]; unsigned char f116; };
void Gap__Core__igArenaMemoryPool__vfunc_32(void *arg0) {
    AP *p = (AP *)arg0;
    if (p->f116 != 0) {
        p->f116 = 0;
        p->vX();
    }
}
