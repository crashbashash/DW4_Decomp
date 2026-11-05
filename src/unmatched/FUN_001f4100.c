int FUN_001f47c0(int, int, int);
int FUN_001f64a0(int, int);
extern int DAT_00568e50[4];
void FUN_001f4100(int a, int b) {
    if (DAT_00568e50[0] == 1) {
        FUN_001f64a0(a, b);
        return;
    }
    FUN_001f47c0(a, b, 0);
}
