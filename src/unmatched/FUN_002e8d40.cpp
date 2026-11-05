class VC_108_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
class VC_208_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
struct R { char pad[4]; int f4; };
struct Q { char pad[24]; R *f24; };
struct G { char pad[8]; int f8; };
struct A { char pad[28]; R *f28; char pad2[72]; VC_108_3 *f104; char pad3[60]; unsigned char f168; char pad4[35]; VC_208_2 *f204; char pad5[4]; unsigned char f212; char pad6[7]; int f220; };
extern "C" {
Q *FUN_002d7e90(...);
int igObject_Destroy(...);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern G *DAT_00586280[4];
}
extern "C" void FUN_002e8d40(int *arg0, A *arg1) {
    R *temp_s0;
    R *t;

    if (arg1->f212 != 0) {
        if (arg1->f104->vX((int)((char *)arg1 + DAT_00586280[0]->f8), 4, 1) != 1) {
            *arg0 = DAT_004fb418[0];
            return;
        }
        if (arg1->f168 != 0) {
            arg1->f204->vX((int)((char *)arg1 + DAT_00586280[0]->f8), 1);
        }
        temp_s0 = FUN_002d7e90(arg1, arg1->f220)->f24;
        if (temp_s0 != 0) {
            temp_s0->f4 = temp_s0->f4 + 1;
        }
        t = arg1->f28;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg1->f28 = temp_s0;
    }
    *arg0 = DAT_004fb410[0];
}
