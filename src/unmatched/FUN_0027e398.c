int strncpy();
extern int DAT_004bb040[4];
extern int DAT_00570bb0[4];
void FUN_0027e398(int arg0) {
    strncpy(&DAT_004bb040[0], arg0, 0x7F);
    if (*(int *)((char *)&(DAT_00570bb0[0]) + 0) != 0) {
        ((int (*)())*(int *)((char *)&(DAT_00570bb0[0]) + 0))(*(int *)((char *)&(DAT_00570bb0[0]) + 4), &DAT_004bb040[0]);
    }
}
