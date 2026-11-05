extern "C" {
void FUN_0015b7d0(...);
void FUN_0015b7f0(...);
void FUN_0015b820(...);
int Memory_FreeBuffer(...);
struct AL;
AL *igObject_GetAllocator(...);
}
class AL { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual char *vX(int); };
class PV { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual char *vX(unsigned); };
struct PA { int vt; int pad1[2]; unsigned n; char pad2[16]; int stride; char *data; char pad3[52]; unsigned char flag; };
extern "C" void Gap__Gfx__igPsx2ParticleArray__vfunc_19(PA *arg0) {
    char *d;
    char *e;
    unsigned i;
    char *buf;
    if (arg0->flag != 0) {
        buf = ((AL *)igObject_GetAllocator(arg0))->vX(arg0->stride * arg0->n);
        for (i = 0; i < arg0->n; i++) {
            e = ((PV *)arg0)->vX(i);
            d = buf + i * arg0->stride;
            FUN_0015b820(d, e);
            FUN_0015b820(d + 12, e + 12);
            FUN_0015b820(d + 24, e + 24);
            FUN_0015b7f0(d + 36, e + 36);
            FUN_0015b7f0(d + 52, e + 52);
            FUN_0015b7f0(d + 68, e + 68);
            FUN_0015b7d0(d + 84, e + 84);
            FUN_0015b7d0(d + 92, e + 92);
            FUN_0015b7d0(d + 100, e + 100);
            FUN_0015b7d0(d + 108, e + 108);
            FUN_0015b7d0(d + 116, e + 116);
            FUN_0015b820(d + 124, e + 124);
            FUN_0015b7d0(d + 136, e + 136);
        }
        if (arg0->data != 0) {
            Memory_FreeBuffer(arg0->data);
        }
        arg0->data = buf;
    }
}
