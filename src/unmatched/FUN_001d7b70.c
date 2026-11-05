int FUN_001b1030();
int FUN_001b1100();
int FUN_001b12f0();
int FUN_001b13d0();
int FUN_001d6a70();
int FUN_001d7120();
int FUN_001d7630();
int FUN_001d7910();
int FUN_001d9ac0();
int FUN_001db720();
int FUN_001dc500();
int FUN_001dc610();
int FUN_001e04c0();
extern int DAT_00562640[4];
extern int DAT_005628e0[4];
extern int DAT_005628e8[4];
extern int DAT_005628f8[4];
extern int DAT_00562908[4];
extern int DAT_00562910[4];
extern int DAT_00562938[4];
extern int DAT_00562940[4];
extern int DAT_00562948[4];
extern int DAT_00562968[4];
extern int DAT_00562988[4];
extern int DAT_00562990[4];
extern int DAT_00562998[4];
extern int DAT_005629a0[4];
extern int DAT_005629a8[4];
extern int DAT_005629b0[4];
extern int DAT_005629b8[4];
extern int DAT_005629c0[4];
extern int DAT_005629c8[4];
extern int DAT_005629d0[4];
extern int DAT_005629d8[4];
extern int DAT_005629e0[4];
extern int DAT_005629e8[4];
extern int DAT_005629f0[4];
typedef struct L { char p[8]; int n; char q[4]; int *arr; } L;
typedef struct S0 {
    char p0[28]; L *f28; unsigned char b32; char p1[51]; L *f84; char p2[4]; int f92; int f96; int f100;
    char p3[36]; unsigned char b140; char p4[7]; int f148; char p5[4]; int f156; char p6[16]; int f176;
    char p7[16]; int f196; int f200; int f204; char p8[20]; int f228;
} S0;
typedef struct S1 { char p[52]; int f52; char p1[12]; int f68; } S1;
void FUN_001d7b70(S0 *arg0, S1 *arg1) {
    int var_s5;
    int var_s6;
    int temp_s5;
    int var_s3;
    int var_s5_2;
    L *temp_v0_2;
    int var_s2;
    int temp_s2;
    int temp_s4;
    int temp_s3;
    int temp_s2_2;
    int temp_s5_2;
    int temp_s2_3;
    L *temp_v0;

    if (arg0->b32 == 0) {
        FUN_001d6a70();
        FUN_001d7120(arg0);
        FUN_001d7910();
        arg0->b32 = 1;
    }
    FUN_001d7630(arg0, (char *)arg1 + 164);
    temp_s4 = DAT_00562640[0];
    DAT_00562640[0] = DAT_005628e0[0];
    if (arg0->b140 != 0) {
        temp_s2 = arg1->f52;
        FUN_001dc500(arg1->f68, 0, 1);
        FUN_001b12f0(temp_s2, arg0->f148);
        FUN_001b12f0(temp_s2, arg0->f176);
        FUN_001d9ac0(arg1->f68, DAT_00562940[0], temp_s2);
        FUN_001b13d0(temp_s2, arg0->f176);
        FUN_001b12f0(temp_s2, DAT_005629d0[0]);
        FUN_001b12f0(temp_s2, DAT_005628f8[0]);
        FUN_001b12f0(temp_s2, DAT_00562910[0]);
        FUN_001b12f0(temp_s2, DAT_00562948[0]);
        FUN_001b12f0(temp_s2, arg0->f196);
        FUN_001b12f0(temp_s2, DAT_00562998[0]);
        FUN_001b1030(temp_s2, arg0->f92);
        FUN_001b1030(temp_s2, arg0->f96);
        FUN_001b1030(temp_s2, arg0->f228);
        temp_s5 = arg0->f84->n;
        for (var_s3 = 0; var_s3 < temp_s5; var_s3++) {
            FUN_001e04c0(arg1, arg0->f84->arr[var_s3]);
        }
        FUN_001b1100(temp_s2, arg0->f228);
        FUN_001b1100(temp_s2, arg0->f96);
        FUN_001b1100(temp_s2, arg0->f92);
        FUN_001b13d0(temp_s2, DAT_00562998[0]);
        FUN_001b13d0(temp_s2, arg0->f196);
        FUN_001b13d0(temp_s2, DAT_00562948[0]);
        FUN_001b13d0(temp_s2, DAT_00562910[0]);
        FUN_001b13d0(temp_s2, DAT_005628f8[0]);
        FUN_001b13d0(temp_s2, DAT_005629d0[0]);
        FUN_001b13d0(temp_s2, arg0->f148);
        FUN_001dc610(arg1->f68);
    }
    DAT_00562640[0] = DAT_005628e8[0];
    temp_s3 = arg1->f52;
    FUN_001dc500(arg1->f68, 0, 0);
    temp_v0 = arg0->f28;
    var_s5 = 0;
    if (temp_v0 != 0) {
        var_s5 = temp_v0->n;
    }
    for (var_s2 = 0; var_s2 < var_s5; var_s2++) {
        FUN_001e04c0(arg1, arg0->f28->arr[var_s2]);
    }
    FUN_001b12f0(temp_s3, DAT_00562998[0]);
    FUN_001b12f0(temp_s3, DAT_005629c0[0]);
    FUN_001b12f0(temp_s3, DAT_005628f8[0]);
    FUN_001b12f0(temp_s3, DAT_00562988[0]);
    FUN_001b12f0(temp_s3, DAT_005629c8[0]);
    temp_s2_2 = arg1->f52;
    FUN_001b12f0(temp_s2_2, DAT_005629a8[0]);
    FUN_001b12f0(temp_s2_2, DAT_005629b0[0]);
    FUN_001b12f0(temp_s2_2, DAT_005629b8[0]);
    FUN_001b12f0(temp_s2_2, DAT_00562910[0]);
    FUN_001db720(arg1->f68, DAT_005629a0[0], temp_s2_2);
    FUN_001b13d0(temp_s2_2, DAT_00562910[0]);
    FUN_001b13d0(temp_s2_2, DAT_005629b8[0]);
    FUN_001b13d0(temp_s2_2, DAT_005629b0[0]);
    FUN_001b13d0(temp_s2_2, DAT_005629a8[0]);
    FUN_001b13d0(temp_s3, DAT_005629c8[0]);
    temp_s2_3 = DAT_00562640[0];
    DAT_00562640[0] = DAT_005628e0[0];
    FUN_001b12f0(temp_s3, DAT_00562908[0]);
    FUN_001b12f0(temp_s3, DAT_00562938[0]);
    FUN_001b12f0(temp_s3, arg0->f156);
    FUN_001b12f0(temp_s3, DAT_00562948[0]);
    FUN_001b12f0(temp_s3, arg0->f100);
    FUN_001b12f0(temp_s3, DAT_00562968[0]);
    FUN_001b12f0(temp_s3, arg0->f200);
    temp_v0_2 = arg0->f28;
    var_s6 = 0;
    if (temp_v0_2 != 0) {
        var_s6 = temp_v0_2->n;
    }
    for (var_s5_2 = 0; var_s5_2 < var_s6; var_s5_2++) {
        FUN_001e04c0(arg1, arg0->f28->arr[var_s5_2]);
    }
    FUN_001b13d0(temp_s3, arg0->f200);
    FUN_001b13d0(temp_s3, DAT_00562968[0]);
    FUN_001b13d0(temp_s3, arg0->f100);
    FUN_001b13d0(temp_s3, DAT_00562948[0]);
    FUN_001b13d0(temp_s3, arg0->f156);
    FUN_001b13d0(temp_s3, DAT_00562938[0]);
    FUN_001b13d0(temp_s3, DAT_00562908[0]);
    FUN_001b13d0(temp_s3, DAT_00562988[0]);
    FUN_001b12f0(temp_s3, DAT_00562990[0]);
    FUN_001b12f0(temp_s3, DAT_005629e0[0]);
    FUN_001b12f0(temp_s3, DAT_005629d8[0]);
    FUN_001b12f0(temp_s3, arg0->f204);
    FUN_001b12f0(temp_s3, DAT_005629e8[0]);
    FUN_001b12f0(temp_s3, DAT_005629f0[0]);
    temp_s5_2 = arg1->f52;
    FUN_001b12f0(temp_s5_2, DAT_005629a8[0]);
    FUN_001b12f0(temp_s5_2, DAT_005629b0[0]);
    FUN_001b12f0(temp_s5_2, DAT_005629b8[0]);
    FUN_001b12f0(temp_s5_2, DAT_00562910[0]);
    FUN_001db720(arg1->f68, DAT_005629a0[0], temp_s5_2);
    FUN_001b13d0(temp_s5_2, DAT_00562910[0]);
    FUN_001b13d0(temp_s5_2, DAT_005629b8[0]);
    FUN_001b13d0(temp_s5_2, DAT_005629b0[0]);
    FUN_001b13d0(temp_s5_2, DAT_005629a8[0]);
    FUN_001b13d0(temp_s3, DAT_005629f0[0]);
    FUN_001b13d0(temp_s3, DAT_005629e8[0]);
    FUN_001b13d0(temp_s3, arg0->f204);
    FUN_001b13d0(temp_s3, DAT_005629d8[0]);
    FUN_001b13d0(temp_s3, DAT_005629e0[0]);
    FUN_001b13d0(temp_s3, DAT_00562990[0]);
    FUN_001b13d0(temp_s3, DAT_005628f8[0]);
    FUN_001b13d0(temp_s3, DAT_00562998[0]);
    FUN_001b13d0(temp_s3, DAT_005629c0[0]);
    DAT_00562640[0] = temp_s2_3;
    FUN_001dc610(arg1->f68);
    DAT_00562640[0] = temp_s4;
}
