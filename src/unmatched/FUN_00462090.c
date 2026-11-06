typedef struct S0 { char pad12[12]; int fC; char pad24[8]; int f18; int f1C; int f20; int f24; } S0;
int FUN_00236c40();
int FUN_00236f30();

void FUN_00462090(S0 *arg0) {
    FUN_00236f30(arg0->fC, *(int *)((char *)(*(int *)((char *)(arg0) + 44)) + 8));
    FUN_00236f30(arg0->fC, arg0->f1C);
    FUN_00236f30(arg0->fC, arg0->f20);
    FUN_00236f30(arg0->fC, arg0->f18);
    FUN_00236f30(arg0->fC, arg0->f24);
    FUN_00236c40(arg0->fC, arg0);
}
