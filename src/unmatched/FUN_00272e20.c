extern char DAT_004a930c[];
int FUN_002659a0();
int memset();
extern int DAT_004a9310[4];
extern int DAT_004f0040[4];
extern int DAT_004f0058[4];
void FUN_00272e20(void) {
    FUN_002659a0(&DAT_004f0040[0], *(int *)DAT_004a930c);
    if (*(int *)DAT_004a930c == 0) {
        memset(&DAT_004a9310[0], 0, 0x800);
    }
    *(int *)DAT_004a930c += 1;
    FUN_002659a0(&DAT_004f0058[0]);
}
