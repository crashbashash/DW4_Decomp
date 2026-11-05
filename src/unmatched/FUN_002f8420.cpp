/* 0x002f8420 - FUN_002f8420. Debug listing loop over 46 slots with virtual getters; parameter reused in place for the default string (default compiler). Verified byte-identical by tools/verify.py. */
extern "C" {
int FUN_00304430(...);
int FUN_00304680();
extern char DAT_004fab10[], DAT_004fab20[], DAT_004f90b0[], DAT_004fab30[];
extern char *DAT_004c2170[4];
}
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(int); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void * v88(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void v348(int); };
struct Z { int w[7]; int f28; };
extern "C" void FUN_002f8420(VA *arg0, char *arg1, VB *arg2);
void FUN_002f8420(VA *arg0, char *arg1, VB *arg2) {
    int s0, s1, s2;
    Z *s6;
    s1 = 0;
    s0 = -1;
    if (arg1 == 0) {
        arg1 = DAT_004fab10;
    }
    s2 = 0;
    do {
        if (arg2 == *(VB **)((char *)arg0 + s2 * 144 + 20)) {
            s6 = (Z *)arg2->v88();
            FUN_00304430(DAT_004fab20, arg1, arg0->v104(s2), s6->f28);
            FUN_00304680();
            s1 += 1;
            if (s1 == 1) {
                s0 = s2;
            }
        }
        s2 += 1;
    } while (s2 < 46);
    if (s1 == 0) {
        FUN_00304430(DAT_004f90b0, arg1);
        FUN_00304680();
    }
    arg2->v348(0);
    if (s0 != -1) {
        FUN_00304430(DAT_004fab30, DAT_004c2170[s0], s0);
        FUN_00304680();
    }
}
