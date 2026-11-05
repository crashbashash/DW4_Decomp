typedef struct S { char pad48[48]; int f48; char pad52[432]; int tbl[16]; } S;
int FUN_0030d1d0();

int FUN_002e15a0(S *arg0, int arg1) {
    int temp_a1;

    if (arg1 >= 0 && arg1 < 16) {
        temp_a1 = arg0->tbl[arg1];
        if (temp_a1 != -1) {
            return FUN_0030d1d0(arg0->f48, temp_a1);
        }
    }
    return 0;
}
