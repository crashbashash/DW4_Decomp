int FUN_0012a9f0();
int strncpy();
extern int DAT_004bb040[4];
extern int DAT_00570bb0[4];
void FUN_0027e3e8(int arg0, int arg1) {
    strncpy(&DAT_004bb040[0], arg0, 0x7F);
    FUN_0012a9f0(&DAT_004bb040[0], arg1, 0x7F);
    if (*(int *)((char *)&(DAT_00570bb0[0]) + 0) != 0) {
        ((int (*)())*(int *)((char *)&(DAT_00570bb0[0]) + 0))(*(int *)((char *)&(DAT_00570bb0[0]) + 4), &DAT_004bb040[0]);
    }
}
