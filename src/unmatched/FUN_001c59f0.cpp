extern "C" {
int igMatrix44f_SetIdentity(...);
int FUN_001906d0(...);
int FUN_002fe290(...);
extern int DAT_005612b0[4];
extern int DAT_005612d8[4];
struct OO;
void FUN_001c59f0(OO *arg0, int arg1, int arg2, int arg3);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_156_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(int); };
class DW4VC_164_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int); };
struct LL { char pad[16]; char **items; };
struct OO { char pad[8]; LL *list; };
struct EE { char pad[96]; int f96; };
void FUN_001c59f0(OO *arg0, int arg1, int arg2, int arg3) {
    int i;
    EE *e;

    igMatrix44f_SetIdentity(arg2);
    for (i = 0; i < arg1; i++) {
        e = (EE *)arg0->list->items[i];
        if (FUN_002fe290(((DW4VC_88_0 *)(e))->vX(), DAT_005612b0[0]) != 0) {
            if (e->f96 == 0) {
                ((DW4VC_156_1 *)(e))->vX(arg3);
                FUN_001906d0(arg2, (char *)e + 0x20);
            }
        } else if (FUN_002fe290(((DW4VC_88_0 *)(e))->vX(), DAT_005612d8[0]) != 0) {
            arg3 = ((DW4VC_164_1 *)(e))->vX(arg3);
        }
    }
}
