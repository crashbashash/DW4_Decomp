extern "C" {
int FUN_002f0a60(...);
int FUN_00304430(...);
int FUN_00304680(...);
extern int DAT_004f95c8[4];
extern int DAT_004fab70[4];
extern int DAT_004fab90[4];
extern void ** DAT_00587218[4];
struct E { char p[20]; int f20; char q[120]; };
void FUN_002f8580(E *arg0, int *arg1);
}
class DW4VC_144_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int vX(); };
class DW4VC_260_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual int vX(int, int); };
void FUN_002f8580(E *arg0, int *arg1) {
    int *var_a1;
    int temp_a2;
    int j;
    int i;
    int found;
    var_a1 = arg1;
    if (var_a1 == 0) {
        var_a1 = (int *)(&DAT_004fab70[0]);
    }
    FUN_00304430(var_a1, var_a1);
    FUN_00304680();
    i = 0;
    do {
        temp_a2 = arg0[i].f20;
        found = 0;
        if (temp_a2 != 0) {
            for (j = 0; j < i; j++) {
                int w = arg0[j].f20;
                if (w == temp_a2) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                ((DW4VC_260_2 *)(arg0))->vX((int)(0), (int)(temp_a2));
            }
        }
        i += 1;
    } while (i < 0x2E);
    FUN_00304430(&DAT_004f95c8[0]);
    FUN_00304680();
    FUN_002f0a60(&DAT_004fab90[0]);
    ((DW4VC_144_0 *)(DAT_00587218[0]))->vX();
}
