extern "C" {
/* Matches only with the alternate (combat) compiler build. */
int memset(int *, int, int);
int strcpy(int *, int);
extern int DAT_005873d0[4];
void FUN_003327c0(int arg0) {
    if (arg0 != 0) {
        strcpy(&DAT_005873d0[0], arg0);
        return;
    }
    memset(&DAT_005873d0[0], 0, 0x100);
}
}
