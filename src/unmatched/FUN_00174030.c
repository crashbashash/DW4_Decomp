int FUN_001e74b0();
int FUN_001e7500();
extern int DAT_0056091c[4];
struct O { char pad[1448]; unsigned char f; };
void FUN_00174030(struct O *arg0, int arg1, int arg2) {
    if (arg0->f == (arg2 & 0xFF)) {
        DAT_0056091c[0] += 1;
    }
    arg0->f = arg2;
    if (arg2 != 0) {
        FUN_001e74b0(0xD);
        return;
    }
    FUN_001e7500(0xD);
}
