extern int DAT_00491270[4];
extern int DAT_00491478[4];
extern long long DAT_0056af10[4];
extern int DAT_0056af60[4];
struct S1f8ae0 { char pad[68]; int flags; };
void FUN_001f8ae0(int arg0, struct S1f8ae0 *arg1) {
    DAT_0056af10[0] += 1;
    if (arg1->flags & 2) {
        DAT_00491270[0] = 1;
        arg1->flags = arg1->flags & ~2;
    }
    DAT_0056af60[arg0] = (int)arg1;
    DAT_00491478[0] |= 4;
}
