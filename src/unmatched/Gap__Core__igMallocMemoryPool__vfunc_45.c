int FUN_0012aff0();
int FUN_002f0880();
extern int DAT_004fd3c8[4];
extern int DAT_004fd3d8[4];
extern int DAT_004fd3f0[4];
extern int DAT_004fd400[4];
struct A1 { char p[152]; int f152; };
struct A2 { char p[76]; int f76; };
void Gap__Core__igMallocMemoryPool__vfunc_45(int *arg0, struct A1 *arg1, struct A2 *arg2) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_s2;
    int temp_s1;
    int r;
    int sp6C;
    FUN_002f0880(&sp6C);
    r = sp6C;
    temp_s1 = arg2->f76;
    if (temp_s1 != 0) {
        var_s2 = arg1->f152;
        if (FUN_0012aff0(temp_s1, &DAT_004fd3c8[0]) != 0) {
            var_s2 = 0;
        } else if (FUN_0012aff0(temp_s1, &DAT_004fd3d8[0]) != 0) {
            var_s2 = 1;
        } else if (FUN_0012aff0(temp_s1, &DAT_004fd3f0[0]) != 0) {
            var_s2 = 2;
        } else if (FUN_0012aff0(temp_s1, &DAT_004fd400[0]) != 0) {
            var_s2 = 3;
        }
        arg1->f152 = var_s2;
    }
    *arg0 = r;
}
