typedef struct S { char pad52[52]; int f52; char pad56[176]; int f232; } S;
int FUN_001b12f0();
int FUN_001b13d0();
int FUN_001b3ff0();
int FUN_001ba1a0(int a0, int arg1) {
    S *arg0 = (S *)a0;
    FUN_001b12f0(arg0->f52, arg0->f232);
    FUN_001b3ff0(arg1, arg0);
    FUN_001b13d0(arg0->f52, arg0->f232);
    return 0;
}
