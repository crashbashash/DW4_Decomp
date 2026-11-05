extern char DAT_004ffbe0[];
extern int DAT_004ffbd8[4];
extern int * DAT_00587330[4];
extern int DAT_00587338[4];
void FUN_0032c0c0(void) {
    if (DAT_00587338[0] == 0) {
        if (DAT_00587330[0] == 0) {
            DAT_00587330[0] = (int *)(&DAT_004ffbd8[0]);
        }
    } else {
        DAT_00587330[0] = (int *)DAT_004ffbe0;
    }
}
