extern int DAT_00587340[16];
extern int DAT_00587338[16];
extern int DAT_00587348[16];
extern int DAT_004c2628[16];
extern unsigned char DAT_005549b8;
int FUN_00102e18();
int FUN_0010d1e0();
int FUN_0010d498();
int FUN_0010d940();
int FUN_0010f2f8();
int FUN_001127c8();
int FUN_00113038();
int FUN_00113518();
int FUN_00113568();
int FUN_00116fb0();
int FUN_00117a90();
int FUN_002ee430();

void FUN_0032d080(void) {
    int n;
    int v;
    FUN_00102e18(1);
    if (DAT_00587340[0] != 0) {
        FUN_0010d940(0);
        if (DAT_00587338[0] != 0) {
            FUN_00116fb0(0);
        }
        if (DAT_00587348[0] != 0) {
            while (FUN_00113038(DAT_00587348[0], 0, 0) < 0) {
            }
        }
        while (((FUN_00113568(DAT_00587340[0]) != 0) ^ 1)) {
        }
        while (((FUN_00113518() != 0) ^ 1)) {
        }
        DAT_005549b8 = 1;
    }
    if (DAT_005549b8 != 0) {
        FUN_0010d940(0);
        if (DAT_00587348[0] != 0) {
            FUN_001127c8();
        }
        FUN_0010f2f8();
        v = DAT_00587338[0];
        if (v == 1 || v == 0) {
            FUN_00116fb0(0);
            FUN_00117a90(1);
        } else if (v == 2) {
            FUN_00116fb0(0);
            FUN_00117a90(2);
        }
        FUN_0010d1e0();
        n = DAT_004c2628[0];
        FUN_0010d498(FUN_002ee430(n * 12), n);
    }
}
