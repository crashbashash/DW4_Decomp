int FUN_0030d1d0();
struct S { char pad[48]; int a; char pad2[304]; int tab[32]; };
int FUN_002e1550(struct S *arg0, int arg1) {
    int t;
    if (arg1 >= 0 && arg1 < 32) {
        t = arg0->tab[arg1];
        if (t != -1) {
            return FUN_0030d1d0(arg0->a, t);
        }
    }
    return 0;
}