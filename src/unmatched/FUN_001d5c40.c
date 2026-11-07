extern int DAT_005627e8[4];
extern int DAT_00562858[4];
extern int DAT_00562868[4];
extern int DAT_00562878[4];
extern int DAT_00562810[4];
extern int DAT_00562800[4];
extern int DAT_005628d0[4];
int FUN_001b12f0();
int FUN_001b13d0();
int FUN_001d5a70();
int FUN_001d5e00();
int FUN_001d5e60();
int FUN_001dc500();
int FUN_001dc610();

typedef struct A0 { char pad144[144]; int f90; unsigned char f94; } A0;
typedef struct A1 { char pad52[52]; int f34; char pad56[12]; int f44; char pad72[160]; int fe8; } A1;
void FUN_001d5c40(A0 *arg0, A1 *arg1) {
    int temp_s1;
    int temp_s0;

    temp_s0 = arg1->f34;
    FUN_001dc500(arg1->f44, 0, 0);
    temp_s1 = FUN_001d5a70(arg0, arg1);
    FUN_001b12f0(temp_s0, arg1->fe8);
    if (arg0->f94 != 0) {
        FUN_001d5e60(arg0, arg1);
    }
    FUN_001b12f0(temp_s0, DAT_005627e8[0]);
    FUN_001b12f0(temp_s0, temp_s1);
    FUN_001b12f0(temp_s0, DAT_00562858[0]);
    FUN_001b12f0(temp_s0, DAT_00562868[0]);
    FUN_001b12f0(temp_s0, arg0->f90);
    FUN_001b12f0(temp_s0, DAT_00562878[0]);
    FUN_001b12f0(temp_s0, DAT_00562810[0]);
    FUN_001b12f0(temp_s0, DAT_00562800[0]);
    FUN_001b12f0(temp_s0, DAT_005628d0[0]);
    FUN_001d5e60(arg0, arg1);
    FUN_001b13d0(temp_s0, DAT_005628d0[0]);
    FUN_001b13d0(temp_s0, DAT_00562800[0]);
    FUN_001b13d0(temp_s0, DAT_00562810[0]);
    FUN_001b13d0(temp_s0, DAT_00562878[0]);
    FUN_001b13d0(temp_s0, arg0->f90);
    FUN_001b13d0(temp_s0, DAT_00562868[0]);
    FUN_001b13d0(temp_s0, DAT_00562858[0]);
    FUN_001b13d0(temp_s0, temp_s1);
    FUN_001b13d0(temp_s0, DAT_005627e8[0]);
    FUN_001b13d0(temp_s0, arg1->fe8);
    FUN_001d5e00(arg0, arg1);
    FUN_001dc610(arg1->f44);
}
