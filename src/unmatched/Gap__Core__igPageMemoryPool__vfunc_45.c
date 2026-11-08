int strstr();
int FUN_002f0880();
int FUN_00326330();
extern int DAT_004fd2f8[4];
extern int DAT_004fd300[4];
extern int DAT_004fd328[4];
extern int DAT_004fd340[4];
extern int DAT_004fd368[4];
extern int DAT_004fd3c8[4];
extern int DAT_004fd3d8[4];
extern int DAT_004fd3f0[4];
extern int DAT_004fd400[4];
extern int DAT_004ff230[4];
struct A1 { char p[136]; int f136; int f140; };
struct A2 { char p[48]; int f48; char p2[8]; int f60; char p3[12]; int f76; };
void Gap__Core__igPageMemoryPool__vfunc_45(int *arg0, struct A1 *arg1, struct A2 *arg2) {
    /* matching construct: variant search — decl order [7, 6, 5, 4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_s6;
    int var_s3;
    int var_a1;
    int temp_s5;
    int temp_s4;
    int temp_s3;
    int r;
    int sp8C;

    FUN_002f0880(&sp8C);
    r = sp8C;
    temp_s5 = arg2->f60;
    temp_s4 = arg2->f76;
    temp_s3 = arg2->f48;
    if (temp_s5 != 0) {
        var_s6 = 0;
        if (strstr(temp_s5, &DAT_004fd2f8[0]) != 0) {
            var_s6 |= 1;
        }
        if (strstr(temp_s5, &DAT_004fd300[0]) != 0) {
            var_s6 |= 2;
        }
        if (strstr(temp_s5, &DAT_004ff230[0]) != 0) {
            var_s6 |= 8;
        }
        if (strstr(temp_s5, &DAT_004fd328[0]) != 0) {
            var_s6 |= 4;
        }
        if (strstr(temp_s5, &DAT_004fd340[0]) != 0) {
            var_s6 |= 0x20;
        }
        var_a1 = var_s6;
        if (strstr(temp_s5, &DAT_004fd368[0]) != 0) {
            var_a1 = var_s6 | 0x10;
        }
        FUN_00326330(arg1, var_a1);
    }
    if ((temp_s3 != 0) && (strstr(temp_s3, &DAT_004ff230[0]) != 0)) {
        FUN_00326330(arg1, arg1->f140 | 8);
    }
    if (temp_s4 != 0) {
        var_s3 = arg1->f136;
        if (strstr(temp_s4, &DAT_004fd3c8[0]) != 0) {
            var_s3 = 0;
        } else if (strstr(temp_s4, &DAT_004fd3d8[0]) != 0) {
            var_s3 = 1;
        } else if (strstr(temp_s4, &DAT_004fd3f0[0]) != 0) {
            var_s3 = 2;
        } else if (strstr(temp_s4, &DAT_004fd400[0]) != 0) {
            var_s3 = 3;
        }
        arg1->f136 = var_s3;
    }
    *arg0 = r;
}
