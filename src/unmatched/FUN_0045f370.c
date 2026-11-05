typedef struct T3 { char pad60[60]; unsigned char f3c; } T3;
typedef struct T2 { char pad52[52]; T3 *f34; } T2;
typedef struct T1 { char pad192[192]; unsigned char fc0; } T1;
typedef struct L { char pad8[8]; int cnt; char pad12[4]; int *arr; } L;
typedef struct S { char pad12[12]; T1 *f0c; char pad16[24]; int f28; char pad44[20]; L *f40; char pad68[12]; T2 *f50; } S;
int FUN_001b0aa0();

void FUN_0045f370(S *arg0) {
    T3 *temp_s3; int temp_s2; int var_s1; int var_s0;

    temp_s3 = arg0->f50->f34;
    FUN_001b0aa0(temp_s3, arg0->f28, 0);
    if ((temp_s3->f3c == 0) && (arg0->f0c->fc0 == 0)) {
        temp_s2 = arg0->f40->cnt;
        var_s1 = 0;
        if (0 < temp_s2) {
            var_s0 = 0;
            do {
                FUN_001b0aa0(temp_s3, *(int *)((char *)arg0->f40->arr + var_s0), 1);
                var_s1 += 1;
                var_s0 += 4;
            } while (var_s1 < temp_s2);
        }
    }
}
