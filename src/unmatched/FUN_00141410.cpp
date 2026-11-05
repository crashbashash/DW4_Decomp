/* 0x00141410 - FUN_00141410. Singleton (pointer array form, not gp-relative) vcalls at 120/124; the third parameter of the 120 slot is unsigned, which fixes the argument load order. Alternate -O3. */
extern "C" {
int FUN_0017c7a0(...);
void FUN_00141410(void *arg0, int arg1);
}
class G { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int v120(int, int, unsigned); virtual int v124(int, int, int); };
extern G *DAT_0055f520[4];
struct A { char p[12]; int f12; int f16; char p2[8]; int f28; unsigned char f32; char q[3]; int f36; };
extern "C" {
void FUN_00141410(void *arg0x, int arg1) {
    A *arg0 = (A *)arg0x;
    int temp_s0;
    if (DAT_0055f520[0] != 0) {
        temp_s0 = arg0->f36;
        if (arg0->f32 == 2) {
            FUN_0017c7a0(arg1, arg0->f16, arg0->f12);
            return;
        }
        if (arg0->f16 > 0) {
            DAT_0055f520[0]->v124(arg0->f16, temp_s0, arg0->f12);
        }
        DAT_0055f520[0]->v120(arg0->f16, temp_s0, arg0->f28);
        return;
    }
    FUN_0017c7a0(arg1, arg0->f16, arg0->f12);
}
}
