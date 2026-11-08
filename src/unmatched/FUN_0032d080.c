extern int DAT_00587340[16];
extern int DAT_00587338[16];
extern int DAT_00587348[16];
extern int DAT_004c2628[16];
extern unsigned char DAT_005549b8;
int sceDmaReset();
int sceSifInitCmd();
int FUN_0010d498();
int sceSifInitRpc();
int FUN_0010f2f8();
int FUN_001127c8();
int FUN_00113038();
int sceSifSyncIop();
int sceSifRebootIop();
int FUN_00116fb0();
int sceCdMmode();
int FUN_002ee430();

void FUN_0032d080(void) {
    int n;
    int v;
    sceDmaReset(1);
    if (DAT_00587340[0] != 0) {
        sceSifInitRpc(0);
        if (DAT_00587338[0] != 0) {
            FUN_00116fb0(0);
        }
        if (DAT_00587348[0] != 0) {
            while (FUN_00113038(DAT_00587348[0], 0, 0) < 0) {
            }
        }
        while (((sceSifRebootIop(DAT_00587340[0]) != 0) ^ 1)) {
        }
        while (((sceSifSyncIop() != 0) ^ 1)) {
        }
        DAT_005549b8 = 1;
    }
    if (DAT_005549b8 != 0) {
        sceSifInitRpc(0);
        if (DAT_00587348[0] != 0) {
            FUN_001127c8();
        }
        FUN_0010f2f8();
        v = DAT_00587338[0];
        if (v == 1 || v == 0) {
            FUN_00116fb0(0);
            sceCdMmode(1);
        } else if (v == 2) {
            FUN_00116fb0(0);
            sceCdMmode(2);
        }
        sceSifInitCmd();
        n = DAT_004c2628[0];
        FUN_0010d498(FUN_002ee430(n * 12), n);
    }
}
