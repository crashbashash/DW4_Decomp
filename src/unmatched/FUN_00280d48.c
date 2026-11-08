struct Ctx00280d48 {
    char pad0[160];
    int info;           /* +160 */
    char pad164[2580];
    int handle;         /* +2744 */
};

int FUN_00281a00();
void FUN_00280e38();
void memset();
extern int DAT_004bb104;
extern int DAT_004bb108;
extern struct Ctx00280d48 *DAT_004bb114;
extern int DAT_00570c00[];
extern char DAT_00570d00[];
extern char DAT_005717c0[];
extern struct Ctx00280d48 DAT_00572a00;

int FUN_00280d48(void) {
    int result = -1;
    int req[1];

    if (DAT_004bb104 != 0) {
        DAT_004bb114 = &DAT_00572a00;
        FUN_00281a00(0x100, 0, 0, 8);
        result = DAT_00570c00[0];
        DAT_004bb114->info = DAT_00570c00[1];
        memset(DAT_005717c0, 0, 0x1240);
        memset(DAT_00570d00, 0, 0xA40);
        if (result == 0) {
            req[0] = (int)DAT_005717c0;
            DAT_004bb114->handle = FUN_00281a00(0x1600, req, 1, 4);
        }
        FUN_00280e38();
        if (result == 0) {
            DAT_004bb108 = 1;
        }
    }
    return result;
}
