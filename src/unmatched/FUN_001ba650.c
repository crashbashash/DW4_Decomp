typedef struct S { char p[52]; int f52; char q[176]; int f232; } S;
int FUN_001b1030(int a, int b);
int FUN_001b1100(int a, int b);
int FUN_001d3e20(int a, S *b);

int FUN_001ba650(int a0, int arg1) {
    S *arg0 = (S *)a0;
    FUN_001b1030(arg0->f52, arg0->f232);
    FUN_001d3e20(arg1, arg0);
    FUN_001b1100(arg0->f52, arg0->f232);
    return 0;
}
