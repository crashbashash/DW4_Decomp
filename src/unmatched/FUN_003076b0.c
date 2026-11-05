struct O { int pad[3]; int f12; };
struct O *FUN_00307c10(int, int, int, int);
int FUN_0030b730(int, void *, float);
extern char DAT_004f9a70[];
int FUN_003076b0(int a0, int a1, int a2, float x) {
    struct O *o = FUN_00307c10(a0, a1, a2, 1);
    if (o == 0) {
        return 0;
    }
    FUN_0030b730(o->f12, DAT_004f9a70, x);
    return 1;
}
