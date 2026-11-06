int FUN_0018de10();
int FUN_0023ac20();
int FUN_0023b110();
int igObject_IsKindOf();
int igObject_Destroy();
extern int DAT_005612b0[4];
extern int DAT_005619f8[4];
extern int DAT_00561a38[4];
typedef struct S1 { char pad4[4]; int f4; } S1;
struct Ls { char p[8]; unsigned int n; char q[4]; struct Q **a; };
struct Q { char p[28]; struct Ls *f28; };
struct R { char p[8]; int f8; };
void FUN_0023b140(struct R *arg0, struct Q *arg1) {
    S1 *sp5C;
    S1 *t;
    unsigned int var_s1;
    unsigned int var_s0;
    struct Ls *temp_v0;

    if (igObject_IsKindOf(arg1, DAT_005619f8[0]) != 0) {
        temp_v0 = arg1->f28;
        var_s1 = 0;
        if (temp_v0 != 0) {
            var_s1 = temp_v0->n;
        }
        var_s0 = 0;
        while (var_s0 < var_s1) {
            FUN_0023b140(arg0, arg1->f28->a[var_s0]);
            var_s0 += 1;
        }
    }
    if (igObject_IsKindOf(arg1, DAT_00561a38[0]) != 0) {
        FUN_0023ac20(&sp5C, arg0, arg1);
        FUN_0018de10(arg0->f8, sp5C);
        t = sp5C;
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    } else if (igObject_IsKindOf(arg1, DAT_005612b0[0]) != 0) {
        FUN_0023b110(arg0, arg1);
    }
}
