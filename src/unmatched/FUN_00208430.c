int FUN_001f0500();
typedef struct { char p0[8]; long long f8; char p1[54]; signed char f : 7; } S;

void FUN_00208430(S *arg0) {
    if (arg0->f == 4 && FUN_001f0500(1, arg0->f8) != 0) {
        arg0->f = 5;
    }
}
