class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();  virtual int vX(void *); };
struct R { char pad4[4]; int refs; };
struct N { char pad12[12]; R *f0c; char pad16[936]; N *f3b8; };
struct S { char pad[1552]; N *f610; };
extern "C" {
int igObject_Destroy(...);
VC *FUN_00165d00(...);
void FUN_001788e0(S *arg0);
}
void FUN_001788e0(S *arg0) {
    N *temp_s1;
    N *temp_s0;
    R *temp_a0;

    temp_s1 = arg0->f610;
    if (temp_s1 != 0) {
        do {
            temp_a0 = temp_s1->f0c;
            temp_s0 = temp_s1->f3b8;
            temp_a0->refs = temp_a0->refs - 1;
            if ((temp_a0->refs & 0x7fffff) == 0) {
                igObject_Destroy(temp_a0);
            }
            FUN_00165d00(arg0)->vX(temp_s1);
        } while (temp_s0 != 0);
    }
    arg0->f610 = 0;
}
