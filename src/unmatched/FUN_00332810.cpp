extern "C" {
int memset(int *, int, int);
int strcpy(int *, int);
extern int DAT_005874d0[4];
void FUN_00332810(int arg0) {
    if (arg0 != 0) {
        strcpy(&DAT_005874d0[0], arg0);
        return;
    }
    memset(&DAT_005874d0[0], 0, 0x100);
}
}
