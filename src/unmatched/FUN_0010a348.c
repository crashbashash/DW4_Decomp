typedef struct { char pad[348]; int a; int b; int c; } M;
int FUN_00106c88(M *, int);
void FUN_0010a348(M *m) {
    FUN_00106c88(m, 3);
    if (FUN_00106c88(m, 1)) {
        FUN_00106c88(m, 8);
        FUN_00106c88(m, 8);
        m->a = FUN_00106c88(m, 8);
    }
    m->b = FUN_00106c88(m, 14);
    FUN_00106c88(m, 1);
    m->c = FUN_00106c88(m, 14);
}
