class L { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void vX(int); int references; };
struct A { char p[16]; int f16; char p2[120]; L *f140; unsigned char f144; unsigned char f145; };
extern "C" {
int igObject_Destroy(...);
void Gap__Core__igLightAttr__vfunc_28(A *arg0);
}
void Gap__Core__igLightAttr__vfunc_28(A *arg0) {
    int temp_a1;
    L *temp_a0;

    temp_a1 = arg0->f16;
    if (temp_a1 != -1) {
        temp_a0 = arg0->f140;
        if (temp_a0 != 0) {
            temp_a0->vX(temp_a1);
        }
    }
    arg0->f16 = -1;
    temp_a0 = arg0->f140;
    if (temp_a0 != 0) {
        temp_a0->references = temp_a0->references - 1;
        if (((unsigned long long)((long long)temp_a0->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f140 = 0;
    arg0->f144 = 1;
    arg0->f145 = 1;
}
